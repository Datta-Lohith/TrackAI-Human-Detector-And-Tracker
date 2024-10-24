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
