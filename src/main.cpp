#include "header.h"

#include "RealsenseSensorClass.h"
#include "RealsenseSensorSetter.h"
#include "PicoSensorClass.h"
#include "PicoSensorSetter.h"
#include "PicoListener.hpp"
#include "SensorManager.h"
#include "SensorWrapper.h"

using namespace std;

std::string PICO_ID="0007-0306-0107-0111";
std::string REALSENSE_ID="830612060670";

int main (int argc, char *argv[])
{
    PicoSensorSetter pico_setter;
    pico_setter.initialize();
    std::vector<SensorWrapper> sensors_pico;
    pico_setter.setSensorObject(sensors_pico);

    SensorManager sens_mng_pico;  
    sens_mng_pico.setIdxSerialMap(pico_setter.bm_idx2serial);
    sens_mng_pico.setSensors(sensors_pico);
    sens_mng_pico.activateSensor(PICO_ID);    
    sens_mng_pico.start();      

    RealsenseSensorSetter rs_setter;
    rs_setter.initialize();
    std::vector<SensorWrapper> sensors;
    rs_setter.setSensorObject(sensors);

    SensorManager sens_mng;
    sens_mng.setIdxSerialMap(rs_setter.bm_idx2serial);
    sens_mng.setSensors(sensors);
    sens_mng.activateSensor(REALSENSE_ID);    
    sens_mng.start();      

    cv::Mat color, ir, ir_resize;
    int key = cv::waitKey(20);

    while (true) {
        sens_mng.update();
        sens_mng_pico.update();

        color = sens_mng.getRGBImage();
        ir = sens_mng_pico.getRGBImage();
        cv::resize(ir, ir_resize,cv::Size(),2.0,2.0);

        cv::imshow("color", color);
        if(ir.rows > 0){
            cv::imshow("ir", ir_resize);
        }
        
        if (key == 's') {
            cv::imwrite("ir.jpg",ir_resize);
            cv::imwrite("color.jpg",color);
        }

        if (key == 27) {
            break;
        }
        key = cv::waitKey(10);        
    }
    sens_mng_pico.stop();
    sens_mng.stop();        

    return 0;
}
