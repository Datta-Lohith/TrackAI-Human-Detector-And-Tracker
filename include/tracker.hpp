/**
 * @file tracker.hpp
 * @author Datta Lohith Gannavarapu, Dheeraj Vishnubhotla, Nazrin Gurbanova
 * @brief This file contains the declaration of the Tracker class for object tracking.
 * @version 0.1
 * @date 2024-10-23
 * @copyright Copyright (c) 2024
 *
 * This file defines the Tracker class, which is responsible for tracking objects 
 * in video frames using OpenCV's tracking algorithms. The class provides methods 
 * for initializing the tracker and updating the tracking state based on detected 
 * bounding boxes.
 */

#ifndef __TRACKER_H__
#define __TRACKER_H__
#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <vector>

namespace TrackAI {

    /**
    * @class Tracker
    * @brief A class for tracking objects in video frames.
    *
    * The Tracker class encapsulates the functionality needed to initialize and 
    * manage an object tracker. It uses OpenCV's tracking algorithms to maintain 
    * the position of detected objects across video frames.
    */
    class Tracker {
        bool isInitialized;          ///< Flag indicating whether the tracker has been initialized
        cv::Ptr<cv::Tracker> tracker; ///< Pointer to the OpenCV Tracker object

        public:
            /**
            * @brief Constructs a Tracker object and initializes the tracker.
            *
            * This constructor sets the initial state of the tracker and prepares it 
            * for object tracking.
            */
            Tracker();

            /**
            * @brief Tracks objects in the current frame based on bounding boxes.
            *
            * This method updates the tracker with the current frame and the 
            * corresponding bounding boxes. It computes the new positions of the tracked 
            * objects and updates their locations.
            *
            * @param frame The current video frame in which objects are to be tracked.
            * @param bboxes A vector of bounding boxes for the detected objects.
            */
            void Track(cv::Mat& frame, std::vector<cv::Rect> bboxes);
    };

} // namespace TrackAI

#endif  // __TRACKER_H__
