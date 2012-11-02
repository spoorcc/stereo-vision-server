#include "includes.h"
#include "camera_manager.h"
#include "packet_receiver.h"

#include <time.h>

using namespace std;

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

uint32_t messagesReceivedCount = 0;
uint32_t messagesSentCount = 0;

Camera_Connection connection;

void startCameraManager(void)
{
	cout << "[Camera Manager] Camera Manager started\n";
	connection.chooseEthernetCard();
	thread thread_sendData		= thread(sendDataToCamera);
	thread thread_receiveData	= thread(receiveDataFromCamera);
	thread thread_calMesPS		= thread(calculateMessagesPerSecond);
}

void receiveDataFromCamera(void)
{
	while(1)
	{
	connection.receivePacket();
	messagesReceivedCount ++;
	}
}

void calculateMessagesPerSecond(void)
{
	for(;;)
	{
		Sleep(1000);
		printf("Message sent: %d/sec, received: %d/sec \n",messagesSentCount, messagesReceivedCount);
		messagesSentCount = 0;
		messagesReceivedCount =0 ;
	}
}

void sendDataToCamera(void)
{	
	Camera_Packet packet = Camera_Packet();
	packet.changeAllHeaders(0xB0, 0x0b0b, true);
	string getSpace;
	for(int i = 0; i < 1024; i++)
	{
	packet.addUint8(0xff);
	}
	packet.setPacketLength();

	for(;;)
	{
	cin >> getSpace;
	connection.sendPacket(packet);
	messagesSentCount ++;
	}
}

void showImage(void)
{
}
