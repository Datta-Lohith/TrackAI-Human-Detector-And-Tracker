# Any C++ source files needed to build this target (TrackAI-test).
add_executable(TrackAI-test
  # list of source cpp files:
  main.cpp
  test.cpp
  ../app/detector.cpp
  ../app/tracker.cpp
  ../app/robot.cpp
  ../app/visualizer.cpp
  )

# Any include directories needed to build this target.
# Note: we do not need to specify the include directories for the
# dependent libraries, they are automatically included.
target_include_directories(TrackAI-test PUBLIC
  # list of include directories:
  ${CMAKE_SOURCE_DIR}/include
  ${OpenCV_INCLUDE_DIRS}
	${EIGEN3_INCLUDE_DIR}
  )

# Any dependent libraires needed to build this target.
target_link_libraries(TrackAI-test PUBLIC
  # list of libraries:
  gtest
  ${OpenCV_LIBS} 
  ${EIGEN3_LIBS}
  )

# Enable CMake’s test runner to discover the tests included in the
# binary, using the GoogleTest CMake module.
gtest_discover_tests(TrackAI-test)
