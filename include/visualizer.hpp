/**
 * @file visualizer.hpp
 * @author Datta Lohith Gannavarapu, Dheeraj Vishnubhotla, Nazrin Gurbanova
 * @brief This file contains the declaration of the Visualizer class for displaying 
 *        and saving results of object detection in images and videos.
 * @version 0.1
 * @date 2024-10-23
 * @copyright Copyright (c) 2024
 *
 * This file defines the Visualizer class, which is responsible for creating 
 * bounding boxes around detected objects, displaying the results, and saving 
 * visualized images and videos. The class utilizes OpenCV for image processing 
 * and visualization tasks, enabling efficient review of object detection results.
 */

#ifndef __VISUALIZER_H__
#define __VISUALIZER_H__

#include <opencv2/core/mat.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>

namespace TrackAI {

    /**
    * @class Visualizer
    * @brief A class for visualizing the results of object detection.
    *
    * The Visualizer class provides functionalities to display detected objects in images, 
    * create bounding boxes around them, and save the visualized results to files. 
    */
    class Visualizer {
        public:
            /** 
              * @brief A vector that stores the images to be processed and visualized.
              */
            std::vector<cv::Mat> images;

            /**
              * @brief Displays the results of human detection in the specified image.
              *
              * This method takes a DNN network and an image containing detected humans, 
              * and displays the results in a window. It can handle multiple detections 
              * and visualize bounding boxes around detected humans.
              *
              * @param net The DNN network used for detection.
              * @param human The image containing detected humans.
              */
            void DisplayResults(cv::dnn::Net &net, cv::Mat &human);

            /**
              * @brief Creates bounding boxes around detected objects in the input image.
              *
              * This method processes the detected bounding boxes and draws them on the 
              * input image. It uses class IDs and confidence scores to filter and display 
              * the results.
              *
              * @param indices The indices of the detected objects.
              * @param boxes The raw bounding boxes around detected objects.
              * @param bboxes Output parameter to store the created bounding boxes.
              * @param input_image The image on which bounding boxes will be drawn.
              * @param class_list List of class names for the detected objects.
              * @param class_ids Class IDs corresponding to detected objects.
              * @param confidences Confidence scores for the detections.
              */
            void CreateBoundingBox(std::vector<int> indices, 
                                    std::vector<cv::Rect> boxes,
                                    std::vector<cv::Rect> *bboxes, 
                                    cv::Mat &input_image,
                                    std::vector<std::string> class_list,
                                    std::vector<int> class_ids, 
                                    std::vector<float> confidences);

            /**
              * @brief Saves the processed images to a video file.
              *
              * This method takes a collection of images and saves them as a video file 
              * in the specified format. It handles errors related to file access issues 
              * and ensures the output video is correctly formatted.
              */
            void SaveResults();
    };

} // namespace TrackAI

#endif  // __VISUALIZER_H__
