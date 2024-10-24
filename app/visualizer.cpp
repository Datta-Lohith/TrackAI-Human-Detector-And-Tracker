/**
 * @file visualizer.cpp
 * @author Datta Lohith Gannavarapu, Dheeraj Vishnubhotla, Nazrin Gurbanova
 * @brief This file contains the implementation of the Visualizer class, 
 *        which is responsible for displaying detection results, creating 
 *        bounding boxes around detected objects, and saving the results to a video file.
 * @version 0.1
 * @date 2024-10-23
 * @copyright Copyright (c) 2024
 */

// Define Macros for colors and drawing properties
#define RED cv::Scalar(0, 0, 255)
#define BLUE cv::Scalar(255, 178, 50)
#define YELLOW cv::Scalar(0, 255, 255)
#define BLACK cv::Scalar(0, 0, 0)
#define THICKNESS 1
#define FONT cv::FONT_HERSHEY_SIMPLEX

#include "detector.hpp"
#include <opencv2/highgui.hpp>
#include "../include/visualizer.hpp"

/**
 * @brief Displays the results of the object detection process.
 *
 * This method calculates the inference time and displays it on the provided image.
 * It also shows the image in a window and stores it for later video creation.
 *
 * @param net The DNN network used for inference.
 * @param human The image in which the results will be displayed.
 */
void TrackAI::Visualizer::DisplayResults(cv::dnn::Net &net, cv::Mat &human) {
    std::vector<double> layersTimes;
    double freq = cv::getTickFrequency() / 1000;
    double t = net.getPerfProfile(layersTimes) / freq;
    std::string label = cv::format("Inference time : %.2f ms", t);
    cv::putText(human, label, cv::Point(20, 40), FONT, 0.7, RED);
    cv::namedWindow("Output", cv::WINDOW_NORMAL);
    cv::imshow("Output", human);

    // Storing the images for video creation
    images.push_back(human);
}

/**
 * @brief Creates bounding boxes for detected objects and displays them on the image.
 *
 * This method takes the indices of detected objects and their corresponding bounding boxes,
 * draws the boxes on the input image, and labels them with the class name and index.
 *
 * @param indices A vector of indices corresponding to detected objects.
 * @param boxes A vector of rectangles representing the bounding boxes of detected objects.
 * @param bboxes A pointer to a vector where the created bounding boxes will be stored.
 * @param input_image The image on which the bounding boxes will be drawn.
 * @param class_list A vector of class names corresponding to class IDs.
 * @param class_ids A vector of class IDs for the detected objects.
 * @param confidences A vector of confidence scores for the detected objects.
 */
void TrackAI::Visualizer::CreateBoundingBox(
    std::vector<int> indices, std::vector<cv::Rect> boxes,
    std::vector<cv::Rect> *bboxes, cv::Mat &input_image,
    std::vector<std::string> class_list, std::vector<int> class_ids,
    const std::vector<float> confidences) {
    int id = 0; // Object ID for labeling
    for (int i = 0; i < indices.size(); i++) {
        int idx = indices[i];
        cv::Rect box = boxes[idx];

        int left = box.x;
        int top = box.y;
        int width = box.width;
        int height = box.height;

        bboxes->push_back(cv::Rect(left, top, width, height));
        // Draw bounding box.
        cv::rectangle(input_image, cv::Point(left, top),
                      cv::Point(left + width, top + height), BLUE, 3 * THICKNESS);

        // Get the label for the class name and its confidence.
        std::string label;
        label = class_list[class_ids[idx]] + ":" + std::to_string(++id);

        // Draw class labels.
        int baseLine;
        cv::Size label_size =
            cv::getTextSize(label, FONT, 0.7, THICKNESS, &baseLine);
        int top1 = std::max(top, label_size.height);

        // Draw the label background and the label itself.
        cv::Point tlc = cv::Point(left, top1);
        cv::Point brc = cv::Point(left + label_size.width, top1 + label_size.height + baseLine);
        cv::rectangle(input_image, tlc, brc, BLACK, cv::FILLED);
        cv::putText(input_image, label, cv::Point(left, top1 + label_size.height),
                    FONT, 0.7, YELLOW, THICKNESS);
    }
}

/**
 * @brief Saves the processed images to a video file.
 *
 * This method checks if there are images to save, resizes them to a uniform size,
 * and writes them to a video file in AVI format.
 */
void TrackAI::Visualizer::SaveResults() {
    if (images.empty()) {
        std::cerr << "No images to save to video." << std::endl;
        return;
    }

    std::cout << std::string(20, '!') << "Saving Results to a video" << std::string(20, '!')  << std::endl;

    cv::Size frameSize = images[0].size();

    // Resize all frames to the same size
    for (auto &image : images) {
        if (image.size() != frameSize) {
            cv::resize(image, image, frameSize);
        }
    }
    
    // Use MJPG codec instead of MP4V
    cv::VideoWriter videoWriter("Results/output.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 1, frameSize);

    if (!videoWriter.isOpened()) {
        std::cerr << "Could not open the output video file for write." << std::endl;
        return;
    }

    for (const auto &image : images) {
        videoWriter.write(image);
    }

    videoWriter.release();
    std::cout << "Video saved successfully to /Results/output.avi" << std::endl;
}
