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

uint8_t imageBuffer[921600];
uint32_t messagesReceivedCount = 0;
uint32_t messagesSentCount = 0;

void startCameraManager(void)
{
	cout << "[Camera Manager] Camera Manager started\n";
	//The camera manager act as a client, since the FPGA is just bouncing information back.
	thread thread_msg_per_sec = thread(calculateMessagesPerSecond);

	thread thread_receive = thread(receiveDataFromCamera);
	thread thread_makeImage = thread(maikeImage);
	
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
	boost::array<uint8_t, 1028> bufferArray = {};

	for(;;){
		bufferArray = connection.read();
		messagesReceivedCount++;
		if (bufferArray.at(0) == RAW_RGB_DATA)
		{
			uint16_t temp = (uint16_t) bufferArray.at(1);
			uint16_t temp2 = (uint16_t) bufferArray.at(2);
		
			uint32_t tempStartPixel = ((temp2<<8) + temp) * 128;
			for(int i = 0; i < 128; i++)
			{
				imageBuffer[tempStartPixel + i] =  bufferArray.at(4 + i * 8); 
			}
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

	packet.newPacket(RAW_RGB_DATA,range, READ);
	for (int j = 0; j < 1024; j++)
	{
		if(j % 3 == 0){
			packet.addUint8(0x0F);
		}else if (j % 2 == 0){
			packet.addUint8(0x00);
		}else{
			packet.addUint8(0xFF);
		}
	}

	for(;;)
	{
		range++;
		if(range >= 7200){
			range = 0;
		}
		//packet.changeAllHeaders(RAW_RGB_DATA, range, READ);
		packet.changeRange(range);
		connection.sendPacket(packet);
		messagesSentCount++;

		//boost::this_thread::sleep(boost::posix_time::microseconds(10));//Sleep for img process?
	}
}

void maikeImage(void)
{
	for(;;)
	{
		string msg;
		cin >> msg;
		IplImage* imgTest = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 3);
        for (int i = 0; i < 921600; i++)
        {
			imgTest->imageData[i] = imageBuffer[i];
        }
        cvNamedWindow( "Example1", CV_WINDOW_AUTOSIZE );
        cvShowImage("Example1", imgTest);
        cvWaitKey(0);
        cvReleaseImage( &imgTest );
        cvDestroyWindow("Example1");
	}
}