#pragma comment(lib, "Ws2_32.lib")
#include "camera_connection.h"
#include "highgui.h"
#include <cv.h>

using namespace boost; 

void receiveDataFromCamera(void);
void sendDataToCamera(void);
void connectToCamera(void);
void showImage(void);

void calculateMessagesPerSecond(void);



