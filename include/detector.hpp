/**
 * @file detector.hpp
 * @author Datta Lohith Gannavarapu, Dheeraj Vishnubhotla, Nazrin Gurbanova
 * @brief This file contains the declaration of the Detector class for object detection.
 * @version 0.1
 * @date 2024-10-23
 * @copyright Copyright (c) 2024
 *
 * This file defines the Detector class, which is responsible for loading a 
 * deep learning model for object detection, preprocessing input images, 
 * and postprocessing detection results to extract relevant information.
 */

#ifndef __DETECTOR_H__
#define __DETECTOR_H__
#pragma once

#include <opencv2/core/mat.hpp>
#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/core.hpp>
#include <vector>

namespace TrackAI {

    /**
    * @class Detector
    * @brief A class for handling object detection using a deep learning model.
    *
    * The Detector class encapsulates the functionality required to load a 
    * detection model, preprocess images for the model, and postprocess 
    * the detection results to extract bounding boxes, class IDs, and 
    * confidence scores.
    */
    class Detector {
        float input_height;          ///< The height of the input image for the model
        float input_width;           ///< The width of the input image for the model
        float SCORE_THRESHOLD;       ///< The threshold for filtering low-confidence detections
        float NMS_THRESHOLD;         ///< The threshold for non-maximum suppression

        cv::dnn::Net net;           ///< The DNN model for object detection

        public:
              std::vector<std::string> class_list; ///< List of class names for detected objects

              /**
              * @brief Default constructor for the Detector class.
              *
              * Initializes the Detector with default parameters for input size, 
              * score threshold, and NMS threshold.
              */
              Detector();

              /**
              * @brief Loads the deep learning model for detection.
              *
              * This method loads the model from the specified path and 
              * initializes the DNN network.
              *
              * @param model_path A reference to a string containing the path 
              *                   to the model file.
              * @return The loaded DNN network.
              */
              cv::dnn::Net Load(std::string &model_path);

              /**
              * @brief Preprocesses the input image for the DNN model.
              *
              * This method prepares the input image by resizing and normalizing 
              * it to the required format for the DNN model.
              *
              * @param input The input image to be preprocessed.
              * @param model The DNN model for which the input is being processed.
              * @return A vector of processed images ready for detection.
              */
              std::vector<cv::Mat> PreProcess(cv::Mat &input, cv::dnn::Net &model);

              /**
              * @brief Postprocesses the detection results.
              *
              * This method processes the raw output from the model to extract 
              * bounding boxes, class IDs, and confidence scores, applying 
              * non-maximum suppression to filter out duplicate detections.
              *
              * @param input_image The original input image used for detection.
              * @param detections A vector of raw detection outputs from the model.
              * @param class_ids A pointer to a vector to store detected class IDs.
              * @param confidences A pointer to a vector to store confidence scores.
              * @param boxes A pointer to a vector to store bounding boxes.
              * @param indices A pointer to a vector to store indices of the filtered detections.
              * @return A Mat object representing the processed image with drawn bounding boxes.
              */
              cv::Mat PostProcess(const cv::Mat &input_image, std::vector<cv::Mat> &detections,
                                  std::vector<int> *class_ids, std::vector<float> *confidences,
                                  std::vector<cv::Rect> *boxes, std::vector<int> *indices);

              /**
              * @brief Converts an image to a square format.
              *
              * This method adjusts the input image to a square shape while maintaining 
              * the aspect ratio by padding the image.
              *
              * @param src The source image to be converted.
              * @return A Mat object representing the square image.
              */
              cv::Mat toSquare(const cv::Mat &src);
    };

} // namespace TrackAI

#endif  // __DETECTOR_H__