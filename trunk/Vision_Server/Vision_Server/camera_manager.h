#include "camera_connection.h"
#include "packet_receiver.h"
#include <boost\thread.hpp>

#include "highgui.h"
#include <cv.h>

void receiveDataFromCamera(void);
void sendDataToCamera(void);
void connectToCamera(void);
void showImage(void);

void calculateMessagesPerSecond(void);