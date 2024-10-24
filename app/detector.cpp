/**
 * @file detector.cpp
 * @author Datta Lohith Gannavarapu, Dheeraj Vishnubhotla, Nazrin Gurbanova
 * @brief This file contains the implementation of the Detector class for object detection.
 * @version 0.1
 * @date 2024-10-23
 * @copyright Copyright (c) 2024
 *
 * This file provides the implementation of methods defined in the Detector class,
 * enabling loading a deep learning model, preprocessing input images, and 
 * postprocessing detection results to extract relevant information.
 */

#include "../include/detector.hpp"
#include <fstream>
#include <opencv2/core.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/tracking.hpp>
#include <../include/robot.hpp>
#include <../include/visualizer.hpp>

/**
 * @brief Default constructor for the Detector class.
 *
 * Initializes the input dimensions and threshold values for the model.
 */
TrackAI::Detector::Detector() {
    input_height = 640.0;    ///< Height of the input image
    input_width = 640.0;     ///< Width of the input image
    SCORE_THRESHOLD = 0.45;   ///< Score threshold for filtering detections
    NMS_THRESHOLD = 0.50;     ///< Non-Maximum Suppression threshold
}

/**
 * @brief Loads the deep learning model for detection.
 *
 * This method loads the model from the specified path and initializes the 
 * DNN network for inference.
 *
 * @param model_path A reference to a string containing the path to the 
 *                   model file.
 * @return The loaded DNN network.
 * @throws std::runtime_error If the model fails to load.
 */
cv::dnn::Net TrackAI::Detector::Load(std::string &model_path) {
    class_list.clear();
    class_list.push_back("person");
    net = cv::dnn::readNetFromONNX(model_path);  // Load model from ONNX format
    if (net.empty()) {
        throw std::runtime_error("Failed to load model: " + model_path);
    }
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
    return net;
}

/**
 * @brief Preprocesses the input image for the DNN model.
 *
 * This method converts the input image into a blob suitable for the 
 * YOLO model by resizing and normalizing it.
 *
 * @param input The input image to be preprocessed.
 * @param model The DNN model for which the input is being processed.
 * @return A vector of processed images ready for detection.
 */
std::vector<cv::Mat> TrackAI::Detector::PreProcess(cv::Mat &input, cv::dnn::Net &model) {
    // input = toSquare(input); // Uncomment if using square images

    // Create a matrix called blob
    cv::Mat blob;

    // Convert the input image to a blob suitable for YOLO, resizing it and normalizing.
    cv::dnn::blobFromImage(input, blob, 1.0 / 255.0, 
                            cv::Size(input_width, input_height), cv::Scalar(), 
                            true, false);

    // Set the input blob for the model.
    model.setInput(blob);
    std::vector<cv::Mat> outputs;

    // Forward pass the input blob through the model.
    model.forward(outputs, model.getUnconnectedOutLayersNames());

    return outputs; // Return the output detections
}

/**
 * @brief Postprocesses the detection results.
 *
 * This method processes the raw output from the model to extract bounding 
 * boxes, class IDs, and confidence scores, applying non-maximum suppression 
 * to filter out duplicate detections.
 *
 * @param input_image The original input image used for detection.
 * @param detections A vector of raw detection outputs from the model.
 * @param class_ids A pointer to a vector to store detected class IDs.
 * @param confidences A pointer to a vector to store confidence scores.
 * @param boxes A pointer to a vector to store bounding boxes.
 * @param indices A pointer to a vector to store indices of the filtered detections.
 * @return A Mat object representing the processed image with drawn bounding boxes.
 */
cv::Mat TrackAI::Detector::PostProcess(const cv::Mat &input_image, std::vector<cv::Mat> &detections,
                                       std::vector<int> *class_ids, std::vector<float> *confidences,
                                       std::vector<cv::Rect> *boxes, std::vector<int> *indices) {
    // Scaling factors to map the detection coordinates to the original image.
    float x_factor = input_image.cols / input_width;
    float y_factor = input_image.rows / input_height;

    const int rows = detections[0].size[2];  // Number of detections
    const int dimensions = detections[0].size[1];  // Detection dimensions

    detections[0] = detections[0].reshape(1, dimensions);
    cv::transpose(detections[0], detections[0]);

    float *data = (float*)(detections[0].data);

    // Iterate through the detections and filter out low-confidence results.
    for (int i = 0; i < rows; ++i) {
        float *classes_scores = data + 4;  // Scores start after the first four values

        cv::Mat scores(1, class_list.size(), CV_32FC1, classes_scores);
        cv::Point class_id;
        double max_class_score;
        cv::minMaxLoc(scores, 0, &max_class_score, 0, &class_id);

        // Keep only the detection if the class score exceeds the threshold.
        if (max_class_score > SCORE_THRESHOLD) {
            // Save the class ID and confidence.
            confidences->push_back(max_class_score);
            class_ids->push_back(class_id.x);

            // Extract the bounding box parameters (center, width, height).
            float cx = data[0];  // X center
            float cy = data[1];  // Y center
            float w = data[2];   // Width
            float h = data[3];   // Height

            // Map the coordinates to the original image scale.
            int left = static_cast<int>((cx - 0.5 * w) * x_factor);
            int top = static_cast<int>((cy - 0.5 * h) * y_factor);
            int width = static_cast<int>(w * x_factor);
            int height = static_cast<int>(h * y_factor);

            // Store the bounding box.
            boxes->push_back(cv::Rect(left, top, width, height));
        }
        data += dimensions;  // Move to the next detection
    }

    // Perform Non-Maximum Suppression to filter overlapping bounding boxes.
    cv::dnn::NMSBoxes(*boxes, *confidences, SCORE_THRESHOLD, NMS_THRESHOLD, *indices);

    return input_image; // Return the original image
}

/**
 * @brief Converts an image to a square format.
 *
 * This method adjusts the input image to a square shape while maintaining 
 * the aspect ratio by padding the image.
 *
 * @param src The source image to be converted.
 * @return A Mat object representing the square image.
 */
cv::Mat TrackAI::Detector::toSquare(const cv::Mat &src) {
    int col = src.cols;  // Width of the source image
    int row = src.rows;  // Height of the source image
    int _max = MAX(col, row);  // Get the maximum dimension
    cv::Mat dst = cv::Mat::zeros(_max, _max, CV_8UC3);  // Create a square image
    src.copyTo(dst(cv::Rect(0, 0, col, row)));  // Copy the original image into the square
    return dst; // Return the square image
}
