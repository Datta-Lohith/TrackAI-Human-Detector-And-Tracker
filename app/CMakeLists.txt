find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED COMPONENTS tracking)
# Any C++ source files needed to build this target (trackAI).
add_executable(trackAI
  # list of source cpp files:
  main.cpp
  detector.cpp
  tracker.cpp
  robot.cpp
  visualizer.cpp
  )

# Any include directories needed to build this target.
# Note: we do not need to specify the include directories for the
# dependent libraries, they are automatically included.
target_include_directories(trackAI PUBLIC
  # list inclue directories:
  ${CMAKE_SOURCE_DIR}/include
  ${OpenCV_INCLUDE_DIRS}
	${EIGEN3_INCLUDE_DIR}
)

# Any dependent libraires needed to build this target.
target_link_libraries(trackAI PUBLIC
  # list of libraries
  ${OpenCV_LIBS} 
  ${EIGEN3_LIBS}
  )

  
