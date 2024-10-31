#!/bin/bash

# Install minimal prerequisites
echo "Updating package list and installing prerequisites..."
sudo apt update && sudo apt install -y cmake g++ wget unzip libeigen3-dev graphviz
sudo apt install libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev

# Clone OpenCV repository
echo "Cloning OpenCV repository..."
git clone https://github.com/opencv/opencv.git
cd opencv 
git checkout 4.10.0

# Clone OpenCV contrib modules
echo "Cloning OpenCV contrib repository..."
cd ..
git clone https://github.com/opencv/opencv_contrib.git
cd opencv_contrib
git checkout 4.10.0

# Build OpenCV
echo "Building OpenCV..."
cd ..
cd opencv
mkdir build
cd build

# Configure OpenCV build
cmake -D CMAKE_BUILD_TYPE=RELEASE \
      -D BUILD_EXAMPLES=OFF \
      -D CMAKE_CXX_STANDARD=14 \
      -D CMAKE_CXX_FLAGS="-std=c++14" \
      -D ENABLE_CXX11=ON .. \
      -D BUILD_opencv_apps=OFF \
      -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
      -D BUILD_DOCS=OFF \
      -D BUILD_PERF_TESTS=OFF \
      -D BUILD_TESTS=OFF \
      -D WITH_CUDA=OFF \
      -D CMAKE_INSTALL_PREFIX=/usr/local ..

# Compile and install OpenCV
echo "Installing OpenCV..."
sudo make install
sudo sh -c 'echo "/usr/local/lib" >> /etc/ld.so.conf.d/opencv.conf'
sudo ldconfig


