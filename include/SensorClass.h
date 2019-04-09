#pragma once
#include "header.h"

enum struct SensorType
{
  STEREO,
  TOF
};

/*
typedef std::function<void(void)> _initialize;
typedef std::function<void(void)> _funcobj_start;
typedef std::function<void(void)> _update;
typedef std::function<cv::Mat(void)> _getRGBImage;
typedef std::function<cv::Mat(void)> _getDepthImage;
typedef std::function<void(void)> _stop;
*/
/*
class Sensor{
    public:
        virtual void initialize(std::string _serial_number);
        virtual void start();
        virtual void update();
        virtual cv::Mat getRGBImage();
        virtual cv::Mat getDepthImage();
        virtual CameraParameter getCameraParameter();        
        virtual void stop();

    private:
        std::string serial_number;
        std::string name;
        SensorType type;
        cv::Mat color_img, depth_img;
        CameraParameter camera_param;
};
*/