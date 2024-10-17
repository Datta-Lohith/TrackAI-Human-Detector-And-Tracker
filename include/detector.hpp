/*
@file detector.hpp
@author Datta Lohith Gannavarapu, Dheeraj Vishnubhotla
@brief This file contains the declaration of the Detector class
@version 0.1
@date 2024-10-16

@copyright Copyright (c) 2024
*/

#ifndef __DETECTOR_H__
#define __DETECTOR_H__
#pragma once

#include <iostream>

namespace TrackAI {

    class Detector {
      float input_height;
      float input_width;

    public:
        void Initialize();
        void Detect();
        void PreProcess();
        void PostProcess();
    };
}

#endif  // __DETECTOR_H__