/*
@file tracker.cpp
@author Datta Lohith Gannavarapu, Dheeraj Vishnubhotla
@brief This file contains the implementation of the Tracker class
@version 0.1
@date 2024-10-16

@copyright Copyright (c) 2024
*/

#include "../include/tracker.hpp"

TrackAI::Tracker(){
    input_width = 640;
    input_height = 640;
}

void TrackAI::Tracker::Initialize() {
  std::cout << "Tracker Initialized" << std::endl;
}

void TrackAI::Tracker::Track() {
  std::cout << "Tracking in progress" << std::endl;
}
