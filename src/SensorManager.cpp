#include "SensorManager.h"

void
SensorManager::setIdxSerialMap(std::unordered_map<int, std::string> &_idx2serial, std::unordered_map<std::string, int> &_serial2idx)
{
    idx2serial = _idx2serial;
    serial2idx = _serial2idx;    
}

void
SensorManager::setSensors(std::vector<RealsenseSensor> &_sensor_vec)
{
    sensor_vec = _sensor_vec ;
}

void 
SensorManager::activateSensor(std::string _serial_number){
    int sensor_idx = serial2idx.at(_serial_number);
    present_serial = _serial_number;

    _get_rgb_image_func = [=](cv::Mat &_rgb_img){
            _rgb_img = sensor_vec[sensor_idx].getRGBImage();
            };
    _get_depth_image_func = [=](cv::Mat &_depth_img){
            _depth_img = sensor_vec[sensor_idx].getDepthImage();
            };
    _get_camera_parameter_func = [=](CameraParameter &_camera_param){
            _camera_param = sensor_vec[sensor_idx].getCameraParameter();
            };
    _update_func = [=](){
        sensor_vec[sensor_idx].update();
    };
    _start_func = [=](){
        sensor_vec[sensor_idx].start();
    };
    _stop_func = [=](){
        sensor_vec[sensor_idx].stop();
    };

}

cv::Mat 
SensorManager::getRGBImage()
{
    cv::Mat _rgb;
    _get_rgb_image_func(_rgb);
    return _rgb;
}

cv::Mat 
SensorManager::getDepthImage()
{
    cv::Mat _depth;
    _get_depth_image_func(_depth);
    return _depth;
}        

CameraParameter 
SensorManager::getCameraParameter()
{
    CameraParameter cam_p;
    _get_camera_parameter_func(cam_p);
    return cam_p;
}

void
SensorManager::start()
{
    _start_func();
}

void
SensorManager::stop()
{
    _update_func();
}

void
SensorManager::update()
{
    _update_func();
}
