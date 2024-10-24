#ifndef __DETECTOR_H__
#define __DETECTOR_H__
#pragma once

#include <opencv2/core/mat.hpp>
#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/core.hpp>
#include <vector>

namespace TrackAI {

    class Detector {
        float input_height;          ///< The height of the input image for the model
        float input_width;           ///< The width of the input image for the model
        float SCORE_THRESHOLD;       ///< The threshold for filtering low-confidence detections
        float NMS_THRESHOLD;         ///< The threshold for non-maximum suppression

        cv::dnn::Net net;           ///< The DNN model for object detection

        public:
              std::vector<std::string> class_list; ///< List of class names for detected objects

              Detector();

              cv::dnn::Net Load(std::string &model_path);

              std::vector<cv::Mat> PreProcess(cv::Mat &input, cv::dnn::Net &model);

              cv::Mat PostProcess(const cv::Mat &input_image, std::vector<cv::Mat> &detections,
                                  std::vector<int> *class_ids, std::vector<float> *confidences,
                                  std::vector<cv::Rect> *boxes, std::vector<int> *indices);

              cv::Mat toSquare(const cv::Mat &src);
    };

} // namespace TrackAI

#endif  // __DETECTOR_H__