/*
@file visualizer.hpp
@author Datta Lohith Gannavarapu, Dheeraj Vishnubhotla
@brief This file contains the declaration of the Visualization class
@version 0.1
@date 2024-10-16

@copyright Copyright (c) 2024
*/

#ifndef __VISUALIZER_H__
#define __VISUALIZER_H__
#pragma once

#include <iostream>

namespace TrackAI {

class Visualizer {

 public:
    void DisplayResults();
    void CreateBoundingBox();
    void SaveResults();
};
}

#endif  // __VISUALIZER_H__
