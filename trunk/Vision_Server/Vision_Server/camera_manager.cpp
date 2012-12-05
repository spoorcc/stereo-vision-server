#include "camera_manager.h"

using namespace std;
using namespace boost; 

uint32_t messagesReceivedCount = 0;
uint32_t messagesSentCount = 0;

Camera_Connection connection;

Camera_Manager::Camera_Manager(void)
{
	boost::thread t = boost::thread(&Camera_Manager::startCameraManager,this);
}

void Camera_Manager::startCameraManager(void)
{
	cout << "[Camera Manager] Camera Manager started\n";
	connection.chooseEthernetCard();
	boost::thread thread_sendData		= boost::thread(&Camera_Manager::sendDataToCamera,this);
	boost::thread thread_receiveData	= boost::thread(&Camera_Manager::receiveDataFromCamera,this);
	boost::thread thread_calMesPS		= boost::thread(&Camera_Manager::calculateMessagesPerSecond,this);
	for(;;)
	{
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000)); 
	}
}

void Camera_Manager::receiveDataFromCamera(void)
{
	while(1)
	{
		if(connection.receivePacket())
		{
			messagesReceivedCount ++;
		}
	}
}

void Camera_Manager::calculateMessagesPerSecond(void)
{
	for(;;)
	{
		Sleep(1000);
		printf("Message sent: %d/sec, received: %d/sec \n",messagesSentCount, messagesReceivedCount);
		messagesSentCount = 0;
		messagesReceivedCount =0 ;
	}
}

void Camera_Manager::sendDataToCamera(void)
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
//	cin >> getSpace;
	connection.sendPacket(packet);
	messagesSentCount ++;
	}
}

void Camera_Manager::showImage(void)
{
}
