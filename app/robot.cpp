#include "robot.hpp"


TrackAI::Robot::Robot() 
    : K((cv::Mat_<double>(3, 3) << 600.0, 0, 320.0,
                                   0, 600.0, 240.0,
                                   0, 0, 1.0)),
      R(cv::Mat::eye(3, 3, CV_64F)), 
      T((cv::Mat_<double>(3, 1) << 0, 0, 2.0)) {
    // Default camera intrinsic matrix K
    // Default rotation matrix R (identity matrix, no rotation)
    // Default translation vector T (2 units along the Z-axis)
}


TrackAI::Robot::Robot(cv::Mat my_K, cv::Mat my_R, cv::Mat my_T)
    : K(my_K), R(my_R), T(my_T) {}


void TrackAI::Robot::Run(bool is_camera) {
    std::vector<cv::Mat> detections;
    cv::Mat human;
    std::string model_path = "Data/Model/yolov8s.onnx";
    net = detector.Load(model_path); // Load the YOLO model

    if (is_camera) {
        cv::VideoCapture cap(0); // Open the default camera

        // Check if the camera is successfully opened
        if (!cap.isOpened()) {
            std::cerr << "Error: Could not access the camera." << std::endl;
            return;
        }

        while (true) {
            cv::Mat frame;
            cap >> frame; // Capture a frame from the camera
            
            ProcessImage(frame, detections, human); // Process the captured frame
            
            // Exit on ESC key press
            if (cv::waitKey(25) == 27) {
                break; // Break the loop if ESC is pressed
            }
        }
        cap.release(); // Release the camera
    } else {
        std::string folder_path = "Data/Images/";
        std::vector<std::string> image_files = {"img0.jpg", "img1.jpg", "img2.jpg", 
                                                  "img3.jpg", "img4.jpg", "img5.jpg", 
                                                  "img6.jpg", "img7.jpg", "img8.jpg", 
                                                  "img9.jpg"};

        for (const auto &image_file : image_files) {
            cv::Mat frame = cv::imread(folder_path + image_file); // Load each image

            ProcessImage(frame, detections, human); // Process each image

            cv::waitKey(0); // Wait for a key press before processing the next image
        }
    }
    visualizer.SaveResults(); // Save the results
    cv::destroyAllWindows(); // Close all OpenCV windows
}


void TrackAI::Robot::ProcessImage(cv::Mat &frame, std::vector<cv::Mat> &detections, cv::Mat &human) {
    detections = detector.PreProcess(frame, net);

    std::vector<int> class_ids;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;
    std::vector<int> indices;

    human = detector.PostProcess(frame, detections, &class_ids, &confidences, &boxes, &indices);

    std::cout << "Number of detections: " << indices.size() << std::endl;

    std::vector<cv::Rect> bboxes;
    visualizer.CreateBoundingBox(indices, boxes, &bboxes, frame, 
                                detector.class_list, class_ids, confidences);
    visualizer.DisplayResults(net, human);

    // Transform and print coordinates in robot frame
    CoorInRobotFrame(boxes);
}


void TrackAI::Robot::CoorInRobotFrame(const std::vector<cv::Rect> &detections) {
    // Check if detections are empty
    if (detections.empty()) return;

    // Loop through each detected object
    for (const cv::Rect &bbox : detections) {
        // Calculate the center of the bounding box
        cv::Point2f center(bbox.x + bbox.width / 2.0, bbox.y + bbox.height / 2.0);

        // Create a 3D point in normalized camera coordinates
        cv::Mat normalized_point = (cv::Mat_<double>(3, 1) << center.x, center.y, 1.0);

        // Convert from normalized camera coordinates to camera frame
        cv::Mat camera_frame_point = R * normalized_point + T;

        // Extract the X, Y, Z coordinates in the camera frame or robot frame
        // You can store multiple coordinates if needed
        double x = camera_frame_point.at<double>(0, 0);
        double y = camera_frame_point.at<double>(1, 0);
        double z = camera_frame_point.at<double>(2, 0);

        // Output or process the coordinates as needed
        std::cout << "Object coordinates in robot frame: X=" << x << ", Y=" << y << ", Z=" << z << std::endl;
    }
}
