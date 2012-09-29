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

void startCameraManager(void)
{
	cout << "[Camera Manager] Camera Manager started\n";
	//The camera manager act as a client, since the FPGA is just bouncing information back.

	//connection.connectToCamera(CAMERA_IP,CAMERA_PORT);
	
	thread thread_receive = thread(receiveDataFromCamera);
	thread thread_makeImage = thread(maikeImage);
	  
	thread thread_send = thread(sendDataToCamera);
}

void receiveDataFromCamera(void)
{
	printf("[Camera Manager] start reading data\n");

	Camera_Connection connection(io_service);

	//First buffer array should be read;
	for(;;){
		boost::array<uint8_t, 1028> bufferArray = connection.read();
		if (bufferArray.at(0) == RAW_RGB_DATA)
		{
			uint16_t temp = (uint16_t) bufferArray.at(1);
			uint16_t temp2 = (uint16_t) bufferArray.at(2);
		
			uint32_t tempStartPixel = ((temp2<<8) + temp) * 128;
			//printf("%d\n", tempStartPixel);
			for(int i = 0; i < 128; i++)
			{
				imageBuffer[tempStartPixel + i] =  bufferArray.at(4 + i * 8); 
			}
		}
	}
}

void calculateImageData(boost::array<uint8_t, 1028> bufferArray)
{

}

void sendDataToCamera(void)
{
	printf("[Camera Manager] start sending data\n");
	//Test with Raw RGB
	uint16_t range = 0;

	Camera_Connection connection(io_service);

	for (int i = 0; i < 7200; i++)
	{
		range = i;
		Packet packet = Packet();
		packet.newPacket(RAW_RGB_DATA,range, READ);
		for (int j = 0; j < 1024; j++)
		{
			if(j % 3 == 0){
				packet.addUint8(0x00);
			}else if (j % 2 == 0){
				packet.addUint8(0xFF);
			}else{
				packet.addUint8(0x00);
			}
		}
		//printf((char*) packet.getBuffer());
		connection.sendPacket(packet);
		//string message;
		//cin >> message;
	}
}

void maikeImage(void)
{
	for(;;)
	{
		string msg;
		cin >> msg;
		IplImage* imgTest = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 3);
        for (int i = 0; i < 307200; i++)
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