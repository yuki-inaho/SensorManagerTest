#include "header.h"
#include "RealsenseSensorSetter.h"

using namespace std;


void
RealsenseSensorSetter::initialize(){
    rs2::context ctx;
    auto list = ctx.query_devices(); // Get a snapshot of currently connected devices
    rs2::colorizer colorize_frame;
    int num_sensor = list.size();

    int _sensor_count = 0;
    for (auto&& _dev : ctx.query_devices())
    {
        rs2::pipeline _pipeline;
        rs2::config _cfg;
        _cfg.enable_stream(RS2_STREAM_COLOR, 1280, 720, RS2_FORMAT_BGR8, 30);// BGR
        rs2::pipeline_profile _profile = _pipeline.start(_cfg);

        /// カメラ情報
        std::string name = "Unknown Device";
        if (_dev.supports(RS2_CAMERA_INFO_NAME))
            name = _dev.get_info(RS2_CAMERA_INFO_NAME);

        std::string sn = "########";
        if (_dev.supports(RS2_CAMERA_INFO_SERIAL_NUMBER))
            sn = _dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER); //remove #
        std::cout << name << std::endl;
        std::cout << "serial number = " << sn << std::endl;
        _cfg.enable_device(_dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER));

        bm_idx2serial.insert(bimap_value_t(_sensor_count, sn));
/*
        idx2serial.insert(std::pair<int, std::string>(_sensor_count, sn));
        serial2idx.insert(std::pair<std::string, int>(sn, _sensor_count));
*/
        _pipeline.stop();
        _sensor_count++;
    }
    n_sensor = _sensor_count;
}

void
RealsenseSensorSetter::setSensorObject(std::vector<RealsenseSensor> &_sensor_vec){
    for(int i=0;i<n_sensor;i++){
        RealsenseSensor _sensor;
        _sensor.initialize(bm_idx2serial.left.at(i));
        _sensor_vec.push_back(_sensor);
    }
}

int
RealsenseSensorSetter::getNumSensor(){
    return n_sensor;
}

