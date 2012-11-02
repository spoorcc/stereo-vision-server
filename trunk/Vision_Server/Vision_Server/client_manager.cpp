#include "includes.h"
#include "client_manager.h"

using namespace std;

uint32_t messagesClientReceivedCount = 0;
uint32_t messagesClientSentCount = 0;

string clients[100];

int sizeSendBuffer = 100;
char bufferArraySendChar[100];
uint8_t bufferArraySendCharUint8_t[100];

void startClientManager(void)
{
	//TODO
	cout << "[Client Manager] Client Manager started\n";
	
	thread thread_receive = thread(receiveDataFromClient);
	thread thread_send = thread(sendDataToClient);
	thread thread_calc = thread(calculateClientMessagesPerSecond);
}

void calculateClientMessagesPerSecond(void)
{
	for(;;){
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
		// printf("[Client Manager] Messages sent: %d/sec, received: %d/sec \n", messagesClientSentCount, messagesClientReceivedCount);
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
/*	for (int j = 0; j < 32; j++)
	{
		clientPacket.addUint8(0x00);
	}*/

	for(;;)
	{
		range++;
		if(range >= 1){
			range = 1;
		}

		cin >> bufferArraySendChar;
		for(int i = 0; i < sizeSendBuffer; i++)
		{
			clientPacket.addUint8(bufferArraySendChar[i]);
		}

		connection.sendPacket(clientPacket);

		messagesClientSentCount++;
		clientPacket.reset();

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
		//Listen and return the client IP
		bufferArray.empty();
		string currentClient = connection.read(bufferArray);
		
		messagesClientReceivedCount ++;
		//Check if client exists, else create new client
		bool newClient = true;

		for each(string client in clients)
		{
			if(client.compare(currentClient) == 0)
			{
				newClient = false;
			}
		}
	
		//printf("%.2x\n", currentClient);
		
		cout <<  currentClient << ": " << "\n" ;

		for(int i = 0; i < bufferArray.max_size() ; i ++)
		{
			//Stop reading when we receive a 0x00 at the end of the msg
			if(bufferArray[i] == 0x00)
			{
				break;
			}
			cout << bufferArray[i]; 
		}
		cout << "\n";
	}
}
