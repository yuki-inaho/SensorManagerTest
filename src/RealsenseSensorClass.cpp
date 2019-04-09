#include "RealsenseSensorClass.h"

using namespace std;

void
RealsenseSensor::initialize(std::string _serial_number){
    /// カメラ接続数チェック
    rs2::context ctx;
    auto list = ctx.query_devices(); // Get a snapshot of currently connected devices
    if (list.size() == 0) {
        std::cout << "No device detected" << std::endl;
        return;
    }
    if (list.size() > 1) {
        std::cout << "plsease only one device" << std::endl;
        return;
    }

    /// カメラ設定
//    rs2::pipeline pipeline;
//    rs2::config cfg;
    cfg.enable_stream(RS2_STREAM_COLOR, 1280, 720, RS2_FORMAT_BGR8, 30);// BGR
    cfg.enable_stream(RS2_STREAM_DEPTH, 1280, 720, RS2_FORMAT_Z16, 30);
    cfg.enable_device(_serial_number);

    rs2::pipeline_profile profile = pipeline.start(cfg);
    dev = pipeline.get_active_profile().get_device();
    dev.query_sensors()[0].set_option(rs2_option::RS2_OPTION_ENABLE_AUTO_EXPOSURE, 1);
    dev.query_sensors()[0].set_option(rs2_option::RS2_OPTION_VISUAL_PRESET, rs2_rs400_visual_preset::RS2_RS400_VISUAL_PRESET_HIGH_DENSITY);

    /// カメラパラメータ取得
    auto const cam_p = pipeline.get_active_profile().get_stream(RS2_STREAM_DEPTH).as<rs2::video_stream_profile>().get_intrinsics();
    camera_param.fx = cam_p.fx;
    camera_param.fy = cam_p.fy;
    camera_param.cx = cam_p.ppx;
    camera_param.cy = cam_p.ppy;

    /// カメラ情報
    if (dev.supports(RS2_CAMERA_INFO_NAME))
        name = dev.get_info(RS2_CAMERA_INFO_NAME);

    //std::string sn = "########";
    if (dev.supports(RS2_CAMERA_INFO_SERIAL_NUMBER))
        serial_number = dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER);

    type = SensorType::STEREO;
    pipeline.stop();
}

void
RealsenseSensor::start(){
    rs2::context ctx;
    auto list = ctx.query_devices(); // Get a snapshot of currently connected devices
    if (list.size() == 0) {
        std::cout << "No device detected" << std::endl;
        return;
    }
    if (list.size() > 1) {
        std::cout << "plsease only one device" << std::endl;
        return;
    }
    cfg.enable_stream(RS2_STREAM_COLOR, 1280, 720, RS2_FORMAT_BGR8, 30);// BGR
    cfg.enable_stream(RS2_STREAM_DEPTH, 1280, 720, RS2_FORMAT_Z16, 30);
    cfg.enable_device(serial_number);
    rs2::pipeline_profile profile = pipeline.start(cfg);
    dev = pipeline.get_active_profile().get_device();
    dev.query_sensors()[0].set_option(rs2_option::RS2_OPTION_ENABLE_AUTO_EXPOSURE, 1);
    dev.query_sensors()[0].set_option(rs2_option::RS2_OPTION_VISUAL_PRESET, rs2_rs400_visual_preset::RS2_RS400_VISUAL_PRESET_HIGH_DENSITY);
}

void
RealsenseSensor::update(){
    rs2::frameset frames = pipeline.wait_for_frames();
    rs2::align align(rs2_stream::RS2_STREAM_COLOR );
    auto aligned_frameset = align.process(frames);
    // color
    rs2::frame color_frame = aligned_frameset.get_color_frame();
    cv::Mat _color(cv::Size(1280, 720), CV_8UC3, (void *) color_frame.get_data(), cv::Mat::AUTO_STEP);
    color_img = _color;
    rs2::frame depth_frame = aligned_frameset.get_depth_frame();
    cv::Mat _depth_input(cv::Size(1280, 720), CV_16UC1, (void *) depth_frame.get_data(), cv::Mat::AUTO_STEP);
    depth_img = _depth_input;
}

cv::Mat 
RealsenseSensor::getRGBImage()
{
    return color_img;
}

cv::Mat 
RealsenseSensor::getDepthImage()
{
    return depth_img;
}

CameraParameter
RealsenseSensor::getCameraParameter()
{
    return camera_param;
}

void 
RealsenseSensor::stop()
{
    pipeline.stop();
}
