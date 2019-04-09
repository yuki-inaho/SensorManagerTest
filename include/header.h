#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <omp.h>
#include <chrono>

/// OpenCV
#include <opencv2/opencv.hpp>
/// RealSense
#include <librealsense2/rs.hpp>

/// カメラパラメータ
struct CameraParameter{
    float fx;
    float fy;
    float cx;
    float cy;
    float base_line;
};