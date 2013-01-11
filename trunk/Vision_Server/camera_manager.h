#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include "camera_connection.h"
#include "camera_incoming_data_handler.h"
#include <QObject>
#include <stdio.h>

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

class Camera_Manager : public QObject
{
    Q_OBJECT
public:
    explicit Camera_Manager(QObject *parent = 0);
private:
    Camera_Connection connection;
    Camera_Incoming_Data_Handler dataHandler;
};
#endif /*CAMERA_MANAGER_H*/
