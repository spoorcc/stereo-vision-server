#include "includes.h"
#include "camera_manager.h"
#include "packetReceiver.h""

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


void startCameraManager(void)
{
	cout << "[Camera Manager] Camera Manager started\n";
//The camera manager act as a client, since the FPGA is just bouncing information back.
	thread thread_msg_per_sec = thread(calculateMessagesPerSecond);

	thread thread_receive = thread(receiveDataFromCamera);
	thread thread_showImage = thread(showImage);
	thread thread_send = thread(sendDataToCamera);
}

void calculateMessagesPerSecond(void)
{
	for(;;){
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
		printf("Messages sent: %d/sec, received: %d/sec \n", messagesSentCount, messagesReceivedCount);
		messagesSentCount = 0;
		messagesReceivedCount = 0;
	}
}

void receiveDataFromCamera(void)
{
	printf("[Camera Manager] start reading data\n");

	Camera_Connection connection(io_service, true);
	
	//Creating the buffer before the loop, otherwise it takes extremely much processing time
	boost::array<uint8_t, 260> bufferArray = {};

	for(;;){
		bufferArray = connection.read();
		messagesReceivedCount++;

		switch ( bufferArray.at(0) ) {
		case CAM_CONFIG : 
			//;
        break;
		case PROCES_CONFIG : 
			//;
        break;
		case CALLIB_DATA : 
			//;
        break;
		case RAW_RGB_DATA : 
			//;
        break;
		case FILLED_UP_DATA : 
			filled_up_data(bufferArray);
        break;
		case EQUALIZED_DATA : 
			//;
        break;
		case RECTIFIED_DATA : 
			//;
        break;
		case CORRESPONDENCE : 
			//;
		default : 
		break;
		}
	}
}

void sendDataToCamera(void)
{
	printf("[Camera Manager] start sending data\n");
	
	/////////////////////////////////////////////////////////////
	//Test with Raw RGB
	uint16_t range = 0;

	Camera_Connection connection(io_service, false);
	Packet packet = Packet();

	range = 0;

	//packet.newPacket(FILLED_UP_DATA, range, READ);
	packet.newPacket(0x00, 0x0000, READ);
	for (int j = 0; j < 32; j++)
	{
		packet.addUint8(0x00);
	//	packet.addUint8(0x00);
	//	packet.addUint8(0x00);
	//	packet.addUint8(0x00);
	//	packet.addUint8(0x00);
	//	packet.addUint8(0x00);
	//	packet.addUint8(0x00);
	//	packet.addUint8(0x22);
		/*if(j % 4 == 0){
			packet.addUint8(0xff);
		}
		else if (j % 3 == 0){
			packet.addUint8(0xf3);
		}
		else if (j % 2 == 0){
			packet.addUint8(0xf3);
		}
		else{
			packet.addUint8(0x4);
		}*/
	}

	for(;;)
	{
		range++;
		if(range >= 1){
			range = 1;
		}
		//packet.changeAllHeaders(RAW_RGB_DATA, range, READ);
		// packet.changeRange(range);
		connection.sendPacket(packet);
		messagesSentCount++;

		//boost::this_thread::sleep(boost::posix_time::microseconds(0));//Sleep for img process?
		boost::this_thread::sleep(boost::posix_time::milliseconds(100));
	}
}

void showImage(void)
{
	for(;;){
		string msg;
		cin >> msg;
		if(msg == "1"){
		maikeImage(imageBuffer_cam1);
		}
		else{
		maikeImage(imageBuffer_cam2);
		}
	}
}
