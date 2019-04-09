#pragma once

#include "header.h"
#include "RealsenseSensorClass.h"
#include <functional>

typedef std::function<void(cv::Mat&)> GetRGBImageFunc;
typedef std::function<void(cv::Mat&)> GetDepthImageFunc;
typedef std::function<void(CameraParameter&)> GetCameraParameterFunc;
typedef std::function<void(void)> UpdateFunc;
typedef std::function<void(void)> StartFunc;
typedef std::function<void(void)> StopFunc;

class SensorManager{
    public:
        void setIdxSerialMap(std::unordered_map<int, std::string> &_idx2serial, std::unordered_map<std::string,int> &_serial2idx);
        void setSensors(std::vector<RealsenseSensor> &_sensor_vec);
        void activateSensor(std::string _serial_number);
        void start();
        void stop();
        void update();
        cv::Mat getRGBImage();
        cv::Mat getDepthImage();        
        CameraParameter getCameraParameter();                
        
    private:
        std::string present_serial;

        int n_sensor;
        std::unordered_map<int, std::string> idx2serial;
        std::unordered_map<std::string, int> serial2idx;

        GetRGBImageFunc _get_rgb_image_func;
        GetDepthImageFunc _get_depth_image_func;
        GetCameraParameterFunc _get_camera_parameter_func;
        StartFunc _start_func;
        StopFunc _stop_func;
        UpdateFunc _update_func;

        std::vector<RealsenseSensor> sensor_vec;
};