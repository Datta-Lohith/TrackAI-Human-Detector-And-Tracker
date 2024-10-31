/**
 * @file main.cpp
 * @author Datta Lohith Gannavarapu, Dheeraj Vishnubhotla, Nazrin Gurbanova
 * @brief This file serves as the entry point for the test suite of the TrackAI-Human-Detector-and-Tracker project.
 *        It initializes the Google Test framework and runs all defined test cases.
 * @version 0.1
 * @date 2024-10-23
 * @copyright Copyright (c) 2024
 */

#include <gtest/gtest.h>
#include <iostream>

/**
 * @brief Main function that initializes and runs the Google Test framework.
 *
 * This function takes command-line arguments, initializes Google Test, and
 * runs all the test cases defined in the project. The results of the tests
 * will be output to the console.
 *
 * @param argc Argument count from the command line.
 * @param argv Argument vector from the command line.
 * @return int Returns 0 if all tests pass, or a non-zero value if any tests fail.
 */
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();  // Run all tests and return the result
}
