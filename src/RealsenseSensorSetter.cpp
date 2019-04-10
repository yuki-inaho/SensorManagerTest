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
        _pipeline.stop();

        RealsenseSensor _sensor;
        _sensor.initialize(sn);
        rs_sensor_list.push_back(_sensor);        

        _sensor_count++;
    }
    n_sensor = _sensor_count;
}

void
RealsenseSensorSetter::setSensorObject(std::vector<SensorWrapper> &_sensor_vec){

    for(int i=0;i<n_sensor;i++){
        SensorWrapper _sensor_wrapper;
        
        _sensor_wrapper._get_rgb_image_func = [=](cv::Mat &_rgb){
            _rgb = rs_sensor_list[i].getRGBImage();
        };
        _sensor_wrapper._start_func = [=](){
            rs_sensor_list[i].start();
        };
        _sensor_wrapper._stop_func = [=](){
            rs_sensor_list[i].stop();
        };
        _sensor_wrapper._update_func = [=](){
            rs_sensor_list[i].update();
        };
        _sensor_vec.emplace_back(_sensor_wrapper);
    }
}


int
RealsenseSensorSetter::getNumSensor(){
    return n_sensor;
}

