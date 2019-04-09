#pragma once
#include "header.h"
#include "SensorWrapper.h"
#include "RealsenseSensorClass.h"
#include "RealsenseSensorSetter.h"

typedef std::function<void(cv::Mat&)> GetRGBImageFunc;
typedef std::function<void(cv::Mat&)> GetDepthImageFunc;
typedef std::function<void(CameraParameter&)> GetCameraParameterFunc;
typedef std::function<void(void)> UpdateFunc;
typedef std::function<void(void)> StartFunc;
typedef std::function<void(void)> StopFunc;

class RealsenseSensorSetter{
    public:
        void initialize(); 
        void setSensorObject(std::vector<SensorWrapper> &_sensor_vec);   
        int getNumSensor();
        bimap_t bm_idx2serial;
        
    private:    
        int n_sensor;
        std::vector<RealsenseSensor> rs_sensor_list;        
};