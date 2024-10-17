# TrackAI - Human Detector And Tracker

[![Build Status](https://github.com/Datta-Lohith/TrackAI-Human-Detector-and-Tracker/actions/workflows/run-unit-test-and-upload-codecov.yml/badge.svg)](https://github.com/Datta-Lohith/TrackAI-Human-Detector-and-Tracker/actions/workflows/run-unit-test-and-upload-codecov.yml)
[![codecov](https://codecov.io/gh/Datta-Lohith/TrackAI-Human-Detector-and-Tracker/graph/badge.svg?token=684mJ3W7BC)](https://codecov.io/gh/Datta-Lohith/TrackAI-Human-Detector-and-Tracker)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

## Overview

Perception, Planning, and Controls are the three core components of any autonomous robotic system, working together to allow the robot to understand its environment, make decisions, and execute actions to achieve its objectives. Perception plays a critical role by providing real-time environmental data that is fed into the planning algorithm. This project focuses on designing a perception module, specifically for detecting and tracking humans using a monocular camera mounted on the robot for ACME Robotics. The goal is to enable the robot to recognize the presence of humans and continuously monitor their movements, facilitating collision avoidance and efficient path planning in dynamic environments. Human detection involves identifying humans in the robot’s surroundings, where algorithms process visual data to locate and recognize regions representing human figures. Human tracking involves continuously monitoring and updating the position of one or more individuals across video frames, assigning a unique ID to each human for tracking over time. The robot's ability to detect and track humans is crucial for avoiding collisions, ensuring safe and smooth navigation during delivery tasks.

## Method

The implementation methodology for this project consists of the following steps:

1. **Human Detection**: The project utilizes the YOLOv8 model to detect humans in individual image frames or continuous video streams (sequences of image frames). YOLOv8 processes the visual input and identifies humans within the scene.
2. **Bounding Box Creation**: After detecting humans, the model retrieves the bounding box coordinates for each identified person. These coordinates are used to draw bounding boxes around the detected humans, visually highlighting their positions within the frame.
3. **Human Tracking**: Each detected human is tracked using methods such as **CSRT** (Discriminative Correlation Filter with Channel and Spatial Reliability) or **SORT** (Simple Online and Realtime Tracking). The tracking assigns a unique ID to each person and continuously monitors their location across frames to maintain accurate tracking.
4. **Coordinate Transformation**: The human coordinates derived from the camera’s perspective are then transformed into the robot’s or the world’s coordinate frame, enabling the robot to accurately interpret the human’s position within its operating environment.

The high-level flow of the methodology can be visualized in the activity diagram, outlining how each component interacts within the system.

## Potential Risks

- **Real-Time Processing Delays**: YOLOv8 may introduce processing delays on resource-constrained robot hardware. To mitigate this, the model's size can be optimized, and techniques like quantization can be employed to reduce computational demands. Additionally, selecting more capable hardware or establishing a master-slave connection between the robot and a more powerful processing unit can help ensure the system meets real-time performance requirements.

- **Accurate Tracking**: Human tracking and ID assignment may become unreliable in scenarios involving occlusion or when multiple humans are detected in close proximity. This risk can be mitigated by refining the tracking algorithm, incorporating techniques such as Kalman filtering or deep learning-based tracking to improve robustness in complex environments.

## Activity Diagram

<p align="center">
<img width="60%" alt="Activity Diagram" src="/Activity Diagram.png">
</p>

## Team

[![GitHub Profile](https://img.shields.io/badge/Datta%20Lohith%20Gannavarapu-000000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/datta-lohith)
[![GitHub Profile](https://img.shields.io/badge/Dheeraj%20Vishnubhotla-000000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/VVSDheeraj)
[![GitHub Profile](https://img.shields.io/badge/Nazrin%20Gurbanova-000000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/nazringr)

## Phase 0:
In phase 0 we have started with high level design which is the UML and made activity diagram with classes which will be helpful in understanding the project process flow. 

### Deliverables
[![Phase 0 Video](https://img.shields.io/badge/Explanation%20Video-000000?style=for-the-badge&logo=youtube&logoColor=white)](https://drive.google.com/file/d/1PM65M6P8xBzXUW2DXN79xyw2vE71nDrk/view?usp=sharing)
[![Quad Chart](https://img.shields.io/badge/Quad%20Chart-000000?style=for-the-badge&logo=chartdotjs&logoColor=white)](/Documents/Quad%20Chart.jpg)
[![Proposal Document](https://img.shields.io/badge/Proposal%20Document-000000?style=for-the-badge&logo=adobeacrobatreader&logoColor=white)](/Documents/Midterm%20Proposal.pdf)
[![UML Diagrams](https://img.shields.io/badge/UML%20Diagram%20Phase%200-000000?style=for-the-badge&logo=uml&logoColor=white)](/UML/Phase%200/UML.pdf)
[![Project Backlog](https://img.shields.io/badge/project%20Backlog-000000?style=for-the-badge&logo=libreofficecalc&logoColor=white)](https://docs.google.com/spreadsheets/d/1fdzaFWkkAuVonq0ZzD6LnyzUNfFDbs992vhskWPqHbA/edit?gid=0#gid=0)


## Code Build Procedure
Follow the below procedure to download the code and start building
```bash
git clone https://github.com/Datta-Lohith/TrackAI-Human-Detector-and-Tracker.git
# Go to the directory where the folder is downloaded
cd TrackAI-Human-Detector-And-Tracker
```
Follow the below procedure to build the code after cloning the repository
```bash
    # Configure the project and generate a native build system:
    # Must re-run this command whenever any CMakeLists.txt file has been changed.
    cmake -S ./ -B build/
    # Compile and build the project:
    # rebuild only files that are modified since the last build
    cmake --build build/
    # Run program:
    ./build/app/trackAI
    # Clean
    cmake --build build/ --target clean
    # Clean and start over:
    rm -rf build/
```

To run the tests and generate code coverage reports:

```bash
    # Run the tests after build
    cd build/
    ctest

    # For Code Coverage Installation and build code coverage report by going to build directory
    cd ..
    sudo apt-get install gcovr lcov
    # Set the build type to Debug and WANT_COVERAGE=ON
    cmake -D WANT_COVERAGE=ON -D CMAKE_BUILD_TYPE=Debug -S ./ -B build/
    # Now, do a clean compile, run unit test, and generate the covereage report
    cmake --build build/ --clean-first --target all test_coverage
    # open a web browser to browse the test coverage report
    # open build/test_coverage/index.html or check in the directory

    # Generating Doxygen Docs 
    cmake --build build/ --target docs
    # Check the Generated Doc HTML by going to docs -> html -> index.html
```

### LICENSE

This project is open source and is released under the MIT License. You are free to use, modify, and distribute the code in accordance with the terms of the MIT License.
