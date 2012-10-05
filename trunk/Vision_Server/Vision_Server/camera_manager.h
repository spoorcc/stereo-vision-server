#pragma comment(lib, "Ws2_32.lib")
#include "camera_connection.h"
#include "highgui.h"
#include <cv.h>

using namespace boost; 
//Camera_Connection connection(boost::asio::io_service);
Camera_Connection connection(boost::asio::io_service&);

boost::asio::io_service io_service;

void receiveDataFromCamera(void);
void sendDataToCamera(void);
void connectToCamera(void);
void showImage(void);

void calculateMessagesPerSecond(void);



