#pragma once
#include "header.h"
//#include "SensorClass.h"
#include "RealsenseSensorClass.h"
#include "RealsenseSensorSetter.h"


class RealsenseSensorSetter{
    public:
        void initialize(); 
        void setSensorObject(std::vector<RealsenseSensor> &_sensor_vec);   
        int getNumSensor();
        std::unordered_map<int, std::string> idx2serial;
        std::unordered_map<std::string, int> serial2idx;
        
    private:    
        int n_sensor;
};