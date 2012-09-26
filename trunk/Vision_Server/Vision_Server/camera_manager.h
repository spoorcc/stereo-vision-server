#pragma comment(lib, "Ws2_32.lib")
#include "camera_connection.h"

void receiveDataFromCamera(void);
void sendDataToCamera(void);
void connectToCamera(void);

Camera_Connection connection;