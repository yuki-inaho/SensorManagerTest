#include "header.h"
#include "RealsenseSensorClass.h"
#include "RealsenseSensorSetter.h"
#include "SensorManager.h"

using namespace std;

std::string REALSENSE_ID="#830612060670";

int image_width = 1280;
int image_height = 720;
float theta_pitch_deg = 0;

int main (int argc, char *argv[])
{
    RealsenseSensorSetter rs_setter;
    rs_setter.initialize();
    cout << rs_setter.getNumSensor() << endl;
    
    std::vector<RealsenseSensor> rs_sensor;

    rs_setter.setSensorObject(rs_sensor);
    SensorManager sens_mng;
    sens_mng.setIdxSerialMap(rs_setter.bm_idx2serial);
    sens_mng.setSensors(rs_sensor);
    std::string sn = "830612060670";
    sens_mng.activateSensor(sn);    
    sens_mng.start();        

    cv::Mat color;
    while (true) {
        sens_mng.update();
        color = sens_mng.getRGBImage();

        cv::imshow("color", color);
        //waitkeyで終了
        if (cv::waitKey(20) == 27) {
            break;
        }
    }
    sens_mng.stop();        

    return 0;
}
    /// read toml file
