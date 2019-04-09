#include "header.h"
#include "RealsenseSensorClass.h"
#include "RealsenseSensorSetter.h"
#include "SensorManager.h"
#include "SensorWrapper.h"

using namespace std;

std::string PICO_ID="0007-0306-0107-0111";
std::string REALSENSE_ID="830612060670";

int image_width = 1280;
int image_height = 720;
float theta_pitch_deg = 0;

int main (int argc, char *argv[])
{
    RealsenseSensorSetter rs_setter;
    rs_setter.initialize();
    std::vector<SensorWrapper> sensors;
    rs_setter.setSensorObject(sensors);

    SensorManager sens_mng;
    sens_mng.setIdxSerialMap(rs_setter.bm_idx2serial);
    sens_mng.setSensors(sensors);
    sens_mng.activateSensor(REALSENSE_ID);    
    sens_mng.start();        

    cv::Mat color;
    while (true) {
        sens_mng.update();
        color = sens_mng.getRGBImage();
        cout << color.rows << endl;
        cv::imshow("color", color);
        //waitkeyで終了
        if (cv::waitKey(20) == 27) {
            break;
        }
    }
    sens_mng.stop();        

    return 0;
}
