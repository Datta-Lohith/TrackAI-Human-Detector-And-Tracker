/**
 * @file tracker.cpp
 * @author Datta Lohith Gannavarapu, Dheeraj Vishnubhotla, Nazrin Gurbanova
 * @brief This file contains the implementation of the Tracker class, which is responsible for 
 *        tracking detected objects in a video frame using the CSRT tracking algorithm.
 * @version 0.1
 * @date 2024-10-23
 * @copyright Copyright (c) 2024
 */

#include "../include/tracker.hpp"

/**
 * @brief Default constructor for the Tracker class.
 *
 * Initializes the tracker using the CSRT algorithm and sets the initialization flag.
 */
TrackAI::Tracker::Tracker() {
    isInitialized = false;  // Flag to check if the tracker is initialized
    tracker = cv::TrackerCSRT::create();  // Create a new CSRT tracker instance
}

/**
 * @brief Tracks objects in the provided video frame.
 *
 * This method either initializes the tracker with the bounding boxes of detected objects
 * or updates the tracker with new positions if it has already been initialized.
 *
 * @param frame The current video frame in which tracking is to be performed.
 * @param bboxes A vector of bounding boxes representing detected objects to track.
 */
void TrackAI::Tracker::Track(cv::Mat& frame, std::vector<cv::Rect> bboxes) {
    if (!isInitialized) {
        // Initialize the tracker with the first set of bounding boxes
        for (cv::Rect& bbox : bboxes) {
            cv::rectangle(frame, bbox, cv::Scalar(0, 0, 0), 2);
            tracker->init(frame, bbox);  // Initialize the tracker
        }
        isInitialized = true;  // Set the initialized flag to true
        return;  // Exit after initialization
    }

    // Update the tracker for each bounding box
    for (cv::Rect& current_box : bboxes) {
        tracker->update(frame, current_box);  // Updating tracker
        cv::rectangle(frame, current_box, cv::Scalar(0, 0, 0), 2);
    }
}
