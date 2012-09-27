#include "includes.h"
#include "camera_manager.h"

using namespace std;

#define CAMERA_IP "127.0.0.1"	//ip address of udp server
#define CAMERA_PORT 51912			//The port on which to listen for incoming data

//Constants
#define CAM_CONFIG		 0x80
#define PROCES_CONFIG	 0x90
#define CALLIB_DATA		 0xA0
#define RAW_RGB_DATA	 0xB0
#define FILLED_UP_DATA	 0xC0
#define EQUALIZED_DATA	 0xD0
#define RECTIFIED_DATA	 0xE0
#define CORRESPONDENCE	 0xF0
#define READ				true
#define WRITE				false

using namespace boost; 

void startCameraManager(void)
{
	cout << "[Camera Manager] Camera Manager started\n";

	//The camera manager act as a client, since the FPGA is just bouncing information back.
	connection = Camera_Connection();
	connection.connectToCamera(CAMERA_IP,CAMERA_PORT);

	thread thread_receive = thread(receiveDataFromCamera);

	sendDataToCamera();
}

void receiveDataFromCamera(void)
{

}

void sendDataToCamera(void)
{
	//Test with Raw RGB
	uint16_t range = 0;
	int sent;
	for (int i = 0; i < 128; i++){
		range = 128 * i;
		Packet packet = Packet(RAW_RGB_DATA,range, READ);
		sent = connection.sendPacket(packet);
		ostringstream stream;  
		if(sent == -1){
			stream << "[ERROR][Camera Manager] Sent " << sent << "\n";
		}else{
			stream << "[Camera Manager] Sent " << sent << "\n";
		}
		cout << stream.str();
	}
}