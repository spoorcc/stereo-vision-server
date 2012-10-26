#include "includes.h"
#include "client_manager.h"

using namespace std;

uint32_t messagesClientReceivedCount = 0;
uint32_t messagesClientSentCount = 0;

void startClientManager(void)
{
	//TODO
	cout << "[Client Manager] Client Manager started\n";
	
	thread thread_receive = thread(receiveDataFromClient);
	//thread thread_send = thread(sendDataToClient);
	thread thread_calc = thread(calculateClientMessagesPerSecond);
}

void calculateClientMessagesPerSecond(void)
{
	for(;;){
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
		printf("Messages sent: %d/sec, received: %d/sec \n", messagesClientSentCount, messagesClientReceivedCount);
		messagesClientSentCount = 0;
		messagesClientReceivedCount = 0;
	}
}

void sendDataToClient(void)
{
	printf("[Client Manager] start sending data\n");
	
	/////////////////////////////////////////////////////////////
	//Test with Raw RGB
	uint16_t range = 0;

	Client_Connection connection(client_io_service, false);
	Client_Packet clientPacket = Client_Packet();

	range = 0;

	//packet.newPacket(FILLED_UP_DATA, range, READ);
	clientPacket.newPacket();
	for (int j = 0; j < 32; j++)
	{
		clientPacket.addUint8(0x00);
	}

	for(;;)
	{
		range++;
		if(range >= 1){
			range = 1;
		}

		connection.sendPacket(clientPacket);
		messagesClientSentCount++;

		boost::this_thread::sleep(boost::posix_time::milliseconds(100));
	}
}

void receiveDataFromClient(void)
{
	printf("[Client Manager] start reading data\n");

	Client_Connection connection(client_io_service, true);
	
	//Creating the buffer before the loop, otherwise it takes extremely much processing time
	boost::array<uint8_t, connection.PACKET_MAXSIZE> bufferArray = {};
	for(;;){
		bufferArray = connection.read();
		//connection
		
	}
}
