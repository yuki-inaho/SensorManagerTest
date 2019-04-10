#pragma once
#include "header.h"
#include "SensorWrapper.h"
#include "PicoSensorClass.h"

typedef std::function<void(cv::Mat&)> GetRGBImageFunc;
typedef std::function<void(cv::Mat&)> GetDepthImageFunc;
typedef std::function<void(CameraParameter&)> GetCameraParameterFunc;
typedef std::function<void(void)> UpdateFunc;
typedef std::function<void(void)> StartFunc;
typedef std::function<void(void)> StopFunc;

class PicoSensorSetter{
    public:
        void initialize(); 
        void setSensorObject(std::vector<SensorWrapper> &_sensor_vec);   
        int getNumSensor();
        bimap_t bm_idx2serial;
        
    private:    
        PicoListener listener;

        int n_sensor;
        CameraManager manager;        
        std::unique_ptr<ICameraDevice> cameraDevice;
        std::vector<PicoSensor> pico_sensor_list;        
};