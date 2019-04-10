cmake_minimum_required(VERSION 3.5)
project(realsense_module)

set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_FLAGS "-O0 -std=gnu++11 -fopenmp")

add_executable(realsense_module src/main.cpp src/RealsenseSensorSetter.cpp src/RealsenseSensorClass.cpp src/SensorManager.cpp src/PicoSensorClass.cpp src/PicoSensorSetter.cpp) 
include_directories(
  include
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(realsense2 realsense2 REQUIRED)
include_directories(${realsense2_CFLAGS})
target_link_libraries(realsense_module ${realsense2_LDFLAGS})

pkg_check_modules(OpenCV opencv REQUIRED)
include_directories(${OpenCV_CFLAGS})
target_link_libraries(realsense_module ${OpenCV_LDFLAGS})

pkg_check_modules(Royale libroyale REQUIRED)
include_directories(${Royale_CFLAGS})
target_link_libraries(realsense_module ${Royale_LDFLAGS})
