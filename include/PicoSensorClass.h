#pragma once
#include "header.h"
#include "PicoListener.hpp"

class PicoSensor{
    public:
        void initialize(std::string _serial_number, std::unique_ptr<ICameraDevice>&& _cameraDevice, PicoListener &listener);
        void start(std::unique_ptr<ICameraDevice>&& cameraDevice);
        void update();
        cv::Mat getRGBImage(PicoListener &listener);
        cv::Mat getDepthImage(PicoListener &listener);
        CameraParameter getCameraParameter(PicoListener &listener);        
        void stop(std::unique_ptr<ICameraDevice>&& cameraDevice);

    private:
        cv::Mat color_img, depth_img;
        CameraParameter camera_param;
        std::string serial_number;
        std::string name;
        SensorType type;
};