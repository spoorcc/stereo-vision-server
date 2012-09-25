#include "includes.h"

using namespace std;

#define SERVER "127.0.0.1"	//ip address of udp server
#define BUFLEN 512	//Max length of buffer
#define PORT 8888	//The port on which to listen for incoming data

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