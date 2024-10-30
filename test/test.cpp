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
std::vector<cv::Rect> bboxes;       ///< Vector to store created bounding boxes
cv::Mat img = cv::imread("../../Data/Images/img0.jpg"); ///< Input image for testing
int width = img.cols;               ///< Width of the input image
std::string model_path = "../../Data/Model/yolov8s.onnx"; ///< Path to the YOLO model

// Instances of classes being tested
TrackAI::Detector detector;         ///< Instance of the Detector class
TrackAI::Visualizer visualizer;     ///< Instance of the Visualizer class
TrackAI::Robot robot;               ///< Instance of the Robot class
TrackAI::Tracker tracker;           ///< Instance of the Tracker class

/**
 * @brief Test case to validate loading of the YOLO model.
 *
 * This test checks if the model is successfully loaded into the net object.
 */
TEST(modeltest, this_is_to_test_yoloModel_function) {
  cv::dnn::Net net = detector.Load(model_path);
  EXPECT_FALSE(net.empty());
}

/**
 * @brief Test case to validate image preprocessing.
 *
 * This test checks if the preprocessing function returns a non-empty result 
 * after processing the input image with the loaded YOLO model.
 */
TEST(preprocess_test, this_is_to_test_preprocessing) {
  cv::dnn::Net net = detector.Load(model_path);
  EXPECT_FALSE(detector.PreProcess(img, net).empty());
}

/**
 * @brief Test case to validate postprocessing of detection results.
 *
 * This test checks if the postprocessing function returns an image of the 
 * same type as the input image after applying detections.
 */
TEST(postprocess_test, this_is_to_test_postprocessing) {
  cv::dnn::Net net = detector.Load(model_path);
  std::vector<cv::Mat> det = detector.PreProcess(img, net);
  EXPECT_EQ(
      detector
          .PostProcess(img, det, &class_ids, &confidences, &boxes, &indices)
          .type(),
      img.type());
}

/**
 * @brief Test case to validate the initialization and update functionality of the Tracker.
 *
 * This test checks if the Tracker can initialize and update with the given bounding boxes.
 */
TEST(HumanTrackerTest, Initialize_Update) {
  bboxes.clear();
  bboxes.push_back(cv::Rect(10, 10, 20, 20));
  bboxes.push_back(cv::Rect(30, 30, 40, 40));

  tracker.Track(img, bboxes);
  EXPECT_EQ(bboxes.size(), 2);
}

/**
 * @brief Test case to validate the bounding box creation in the Visualizer.
 *
 * This test checks if the CreateBoundingBox method successfully adds 
 * a bounding box to the bboxes vector for a detected object.
 */
TEST(VisualizationTest, CreateBoundingBoxTest) {
  indices.push_back(0);
  boxes.push_back(cv::Rect(10, 20, 30, 40));
  class_list.push_back("ClassA");
  class_ids.push_back(0);
  confidences.push_back(0.95);

  visualizer.CreateBoundingBox(indices, boxes, &bboxes, img, class_list,
                                class_ids, confidences);
  ASSERT_EQ(bboxes.size(), 1);
  ASSERT_EQ(bboxes[0], cv::Rect(10, 20, 30, 40));
}
