/**
 * @file test.cpp
 * @author Datta Lohith Gannavarapu, Dheeraj Vishnubhotla, Nazrin Gurbanova
 * @brief This file contains the test cases for the TrackAI-Human-Detector-and-Tracker project.
 *        It utilizes Google Test framework to validate the functionality of the 
 *        Detector, Visualizer, Tracker, and Robot classes.
 * @version 0.1
 * @date 2024-10-23
 * @copyright Copyright (c) 2024
 */

#include <gtest/gtest.h>
#include "../include/robot.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/imgcodecs.hpp"

// Global variables for testing
std::vector<cv::Rect> boxes;        ///< Vector to hold bounding boxes
std::vector<int> indices;           ///< Vector to hold indices of detected objects
std::vector<int> class_ids;         ///< Vector to hold class IDs for detected objects
std::vector<float> confidences;     ///< Vector to hold confidence scores for detections
std::vector<std::string> class_list; ///< Vector to hold class names
cv::Mat img = cv::imread("../../Data/Images/img0.jpg"); ///< Input image for testing
int width = img.cols;               ///< Width of the input image
std::string model_path = "../../Data/Model/yolov8s.onnx"; ///< Path to the YOLO model

// Instances of classes being tested
TrackAI::Detector detector;         ///< Instance of the Detector class

TEST(modeltest, this_is_to_test_yoloModel_function) {
  cv::dnn::Net net = detector.Load(model_path);
  EXPECT_FALSE(net.empty());
}

TEST(preprocess_test, this_is_to_test_preprocessing) {
  cv::dnn::Net net = detector.Load(model_path);
  EXPECT_FALSE(detector.PreProcess(img, net).empty());
}

TEST(postprocess_test, this_is_to_test_postprocessing) {
  cv::dnn::Net net = detector.Load(model_path);
  std::vector<cv::Mat> det = detector.PreProcess(img, net);
  EXPECT_EQ(
      detector
          .PostProcess(img, det, &class_ids, &confidences, &boxes, &indices)
          .type(),
      img.type());
}
