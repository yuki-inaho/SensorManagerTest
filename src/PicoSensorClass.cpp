#include "PicoSensorClass.h"

using namespace std;
using namespace royale;

void
PicoSensor::initialize(std::string _serial_number, std::unique_ptr<ICameraDevice>&& cameraDevice, PicoListener &listener){
    // Pico Flexxの始動処理
    cout << "Trying to open : " << _serial_number << endl;

    // the camera device is now available and CameraManager can be deallocated here
    if (cameraDevice == nullptr)
    {
        // no cameraDevice available
        cerr << "Could not open pico flexx" << endl;
        return;
    }

    // IMPORTANT: call the initialize method before working with the camera device
    auto status = cameraDevice->initialize();
    if (status != CameraStatus::SUCCESS)
    {
        cerr << "Cannot initialize the camera device, error string : " << getErrorString (status) << endl;
        return;
    }
    // retrieve the lens parameters from Royale

    LensParameters lensParameters;
    status = cameraDevice->getLensParameters (lensParameters);
    if (status != CameraStatus::SUCCESS)
    {
        cerr << "Can't read out the lens parameters" << endl;
        return;
    }

    listener.setLensParameters (lensParameters);
    // register a data listener
    if (cameraDevice->registerDataListener (&listener) != CameraStatus::SUCCESS)
    {
        cerr << "Error registering data listener" << endl;
        return;
    }

    // exposure time is available between 100-2000
    if (cameraDevice->setExposureTime(1000) != CameraStatus::SUCCESS) //
    {
        cerr << "Error setting exposure time" << endl;
        return;
    }

    name = "Pico Flexx";
    serial_number = _serial_number;
    type = SensorType::TOF;
}

void
PicoSensor::update(){
    // do nothing
}

void
PicoSensor::start(std::unique_ptr<ICameraDevice>&& cameraDevice){
    if (cameraDevice->startCapture() != CameraStatus::SUCCESS)
    {
        cerr << "Error starting the capturing" << endl;
        return ;
    }
}

void
PicoSensor::stop(std::unique_ptr<ICameraDevice>&& cameraDevice){
    // stop capture mode
    if (cameraDevice->stopCapture() != CameraStatus::SUCCESS)
    {
        cerr << "Error stopping the capturing" << endl;
        return;
    }
}

cv::Mat
PicoSensor::getRGBImage(PicoListener &listener){
    return listener.getGrayMat();
}

cv::Mat
PicoSensor::getDepthImage(PicoListener &listener){
    return listener.getZMat();
}

CameraParameter
PicoSensor::getCameraParameter(PicoListener &listener){
    return listener.getCameraParameter();
}

