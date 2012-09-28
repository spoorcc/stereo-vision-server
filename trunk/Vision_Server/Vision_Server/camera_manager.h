#pragma comment(lib, "Ws2_32.lib")
#include "camera_connection.h"

void receiveDataFromCamera(void);
void sendDataToCamera(void);
void connectToCamera(void);
void maikeImage(void);

#include "highgui.h"
#include <cv.h>

Camera_Connection connection;