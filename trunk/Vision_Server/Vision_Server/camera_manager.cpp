#include "includes.h"
#include "camera_manager.h"

using namespace std;

#define CAMERA_SERVER "127.0.0.1"	//ip address of udp server
#define BUFLEN 1027					//Max length of buffer
#define CAMERA_PORT 51912			//The port on which to listen for incoming data

void startCameraManager(void)
{
	//The camera manager act as a client, since the FPGA is just bouncing information back.
	
	using namespace boost; 

    thread thread_receive = thread(receiveDataFromCamera);
}

void sendDataToCamera(Packet packet)
{
	
}

void receiveDataFromCamera(void)
{

}