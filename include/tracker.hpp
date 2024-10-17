/*
@file tracker.hpp
@author Datta Lohith Gannavarapu, Dheeraj Vishnubhotla
@brief This file contains the declaration of the Tracker class
@version 0.1
@date 2024-10-16

@copyright Copyright (c) 2024
*/

#ifndef __TRACKER_H__
#define __TRACKER_H__
#pragma once

#include <iostream>

namespace TrackAI {
    
    class Tracker {
        float input_height;
        float input_width;

    public:
        void Initialize();
        void Track();
    };
}

#endif  // __TRACKER_H__