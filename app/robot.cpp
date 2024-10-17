/*
@file robot.cpp
@author Datta Lohith Gannavarapu, Dheeraj Vishnubhotla
@brief This file contains the implementation of the Robot class
@version 0.1
@date 2024-10-16

@copyright Copyright (c) 2024
*/

#include "../include/robot.hpp"

void TrackAI::Robot::Initialize() {
  detector.Initialize();
  tracker.Initialize();
}

void TrackAI::Robot::Run() {
  detector.Detect();
  detector.PreProcess();
  detector.PostProcess();
  tracker.Track();
}
