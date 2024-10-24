/**
 * @file robot.hpp
 * @author Datta Lohith Gannavarapu, Dheeraj Vishnubhotla, Nazrin Gurbanova
 * @brief This file contains the declaration of the Robot class for robotic perception and tracking.
 * @version 0.1
 * @date 2024-10-23
 * @copyright Copyright (c) 2024
 *
 * This file defines the Robot class, which integrates object detection and tracking 
 * functionalities for a robotic system. It utilizes OpenCV's DNN module for detection 
 * and provides methods for processing images from a camera or static images.
 */

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

    /**
    * @class Robot
    * @brief A class representing a robotic system for object detection and tracking.
    *
    * The Robot class encapsulates the functionalities needed to detect and track 
    * objects using computer vision techniques. It manages the initialization of 
    * the detector, tracker, and visualizer components and provides methods for 
    * processing images and transforming coordinates.
    */
    class Robot {
        Detector detector;          ///< The object responsible for detecting humans in images
        cv::dnn::Net net;          ///< The DNN model used for detection
        Visualizer visualizer;      ///< The visualizer for displaying results

        cv::Mat K;                 ///< Intrinsic camera matrix
        cv::Mat R;                 ///< Rotation matrix
        cv::Mat T;                 ///< Translation vector

        public:
            /**
            * @brief Default constructor for the Robot class.
            *
            * Initializes the Robot instance with default camera parameters and 
            * prepares the components for detection and tracking.
            */
            Robot();

            /**
            * @brief Parameterized constructor for the Robot class.
            *
            * Initializes the Robot instance with specified camera parameters.
            *
            * @param my_K The intrinsic camera matrix.
            * @param my_R The rotation matrix.
            * @param my_T The translation vector.
            */
            Robot(cv::Mat my_K, cv::Mat my_R, cv::Mat my_T);

            /**
            * @brief Runs the detection and tracking process.
            *
            * This method starts the process of capturing frames from a camera or 
            * using a static image. It calls the appropriate methods to process the 
            * images for detection and tracking.
            *
            * @param is_camera A boolean flag to indicate whether to use the camera 
            *                  (default is true).
            */
            void Run(bool is_camera = true);

            /**
            * @brief Processes a single image for detection and tracking.
            *
            * This method takes an image frame, detects objects, and updates the 
            * tracking state. The results are stored in the provided detections vector.
            *
            * @param frame The input image frame to be processed.
            * @param detections A vector to hold the detection results.
            * @param human A reference to a Mat object for storing human detection data.
            */
            void ProcessImage(cv::Mat &frame, std::vector<cv::Mat> &detections, cv::Mat &human);

            /**
            * @brief Transforms detected coordinates into the robot's reference frame.
            *
            * This method converts the coordinates of detected objects from the 
            * camera frame to the robot frame for further processing and navigation.
            *
            * @param detections A vector of bounding boxes for detected objects.
            */
            void CoorInRobotFrame(const std::vector<cv::Rect> &detections);
        };

} // namespace TrackAI

#endif  // __ROBOT_H__
