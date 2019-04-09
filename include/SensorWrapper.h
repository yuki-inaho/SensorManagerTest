#pragma once
#include "header.h"

typedef std::function<void(cv::Mat&)> GetRGBImageFunc;
typedef std::function<void(cv::Mat&)> GetDepthImageFunc;
typedef std::function<void(CameraParameter&)> GetCameraParameterFunc;
typedef std::function<void(void)> UpdateFunc;
typedef std::function<void(void)> StartFunc;
typedef std::function<void(void)> StopFunc;

struct SensorWrapper{
    GetRGBImageFunc _get_rgb_image_func;
    GetDepthImageFunc _get_depth_image_func;
    GetCameraParameterFunc _get_camera_parameter_func;
    StartFunc _start_func;
    StopFunc _stop_func;
    UpdateFunc _update_func;
};