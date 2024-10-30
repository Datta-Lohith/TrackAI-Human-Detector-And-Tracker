/**
 * @file main.cpp
 * @author Datta Lohith Gannavarapu, Dheeraj Vishnubhotla, Nazrin Gurbanova
 * @brief This file contains the main function to run the TrackAI application.
 * @version 0.1
 * @date 2024-10-23
 * @copyright Copyright (c) 2024
 *
 * This file serves as the entry point for the TrackAI application, initializing
 * the Robot object and starting the robot's operation.
 */

#include <iostream>
#include "../include/robot.hpp"

/**
 * @brief The main function of the TrackAI application.
 *
 * Initializes a Robot instance and calls the Run method to start the 
 * detection and tracking process.
 *
 * @return int Returns 0 upon successful execution.
 */
int main() {
    TrackAI::Robot robot; ///< Create an instance of the Robot class
    robot.Run(true);      ///< Start the robot operation, with camera input disabled
    return 0;             ///< Return success
}
