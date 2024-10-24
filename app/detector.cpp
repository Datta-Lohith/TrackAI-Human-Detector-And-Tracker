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

TrackAI::Detector::Detector() {
    input_height = 640.0;    ///< Height of the input image
    input_width = 640.0;     ///< Width of the input image
    SCORE_THRESHOLD = 0.45;   ///< Score threshold for filtering detections
    NMS_THRESHOLD = 0.50;     ///< Non-Maximum Suppression threshold
}

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


cv::Mat TrackAI::Detector::toSquare(const cv::Mat &src) {
    // STUB Implementation
    return src;
}
