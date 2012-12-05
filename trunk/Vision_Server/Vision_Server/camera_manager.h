#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include "camera_connection.h"

#include <boost\thread.hpp>
#include <highgui.h>
#include <cv.h>

//Constants
#define CAM_CONFIG 0x80
#define PROCES_CONFIG	 0x90
#define CALLIB_DATA		 0xA0
#define RAW_RGB_DATA	 0xB0
#define FILLED_UP_DATA	 0xC0
#define EQUALIZED_DATA	 0xD0
#define RECTIFIED_DATA	 0xE0
#define CORRESPONDENCE	 0xF0
#define READ				true
#define WRITE				false

class Camera_Manager {
public:
	Camera_Manager::Camera_Manager(void);
	void Camera_Manager::startCameraManager(void);
	void Camera_Manager::receiveDataFromCamera(void);
	void Camera_Manager::sendDataToCamera(void);
	void Camera_Manager::connectToCamera(void);
	void Camera_Manager::showImage(void);
	void Camera_Manager::calculateMessagesPerSecond(void);
};
#endif

