#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <omp.h>
#include <chrono>

#include <boost/bimap/bimap.hpp>
#include <functional>

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

enum struct SensorType
{
  STEREO,
  TOF
};

typedef boost::bimaps::bimap<int, std::string> bimap_t;
typedef bimap_t::value_type bimap_value_t;
