#ifndef __ROBOT_H__
#define __ROBOT_H__
#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "detector.hpp"
#include "tracker.hpp"
#include "visualizer.hpp"

namespace TrackAI {

    class Robot {
        Detector detector;          ///< The object responsible for detecting humans in images
        cv::dnn::Net net;          ///< The DNN model used for detection
        Visualizer visualizer;      ///< The visualizer for displaying results

        cv::Mat K;                 ///< Intrinsic camera matrix
        cv::Mat R;                 ///< Rotation matrix
        cv::Mat T;                 ///< Translation vector

        public:
            Robot();
            Robot(cv::Mat my_K, cv::Mat my_R, cv::Mat my_T);

            void Run(bool is_camera = true);
            void ProcessImage(cv::Mat &frame, std::vector<cv::Mat> &detections, cv::Mat &human);

            void CoorInRobotFrame(const std::vector<cv::Rect> &detections);
        };

} // namespace TrackAI

#endif  // __ROBOT_H__
