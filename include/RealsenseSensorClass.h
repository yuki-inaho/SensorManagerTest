#pragma once
#include "header.h"

class RealsenseSensor{
    public:
        void initialize(std::string _serial_number);
        void start();
        void update();
        cv::Mat getRGBImage();
        cv::Mat getDepthImage();
        CameraParameter getCameraParameter();        
        void stop();

    private:
        cv::Mat color_img, depth_img;
        CameraParameter camera_param;
        std::string serial_number;
        std::string name;
        SensorType type;

        std::vector<RealsenseSensor> rs_sensor_list;
        rs2::pipeline pipeline;
        rs2::config cfg;
        rs2::device dev;
};