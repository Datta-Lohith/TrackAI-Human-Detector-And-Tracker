/*
@file robot.hpp
@author Datta Lohith Gannavarapu, Dheeraj Vishnubhotla
@brief This file contains the declaration of the Robot class
@version 0.1
@date 2024-10-16

@copyright Copyright (c) 2024
*/

#ifndef __ROBOT_H__
#define __ROBOT_H__
#pragma once

#include <iostream>
#include "detector.hpp"
#include "tracker.hpp"
#include "visualizer.hpp"


namespace TrackAI {
    
    class Robot {
        Detector detector;
        Tracker tracker;
        Visualizer visualizer;

    public:
        void Initialize();
        void Run();
    };
}

#endif  // __ROBOT_H__