#include "includes.h"
#include "client_manager.h"

uint32_t messagesClientReceivedCount = 0;
uint32_t messagesClientSentCount = 0;

std::list<Client*> clients;

//TODO
#define Client_ip  "1.2.3.4" //"145.48.115.192" //"192.168.123.4" 

void startClientManager(void)
{
	//TODO
	cout << "[Client Manager] Client Manager started\n";
	
	thread thread_receive = thread(receiveDataFromClient);

	thread thread_calc = thread(calculateClientMessagesPerSecond);
}

void calculateClientMessagesPerSecond(void)
{
	for(;;){
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
		printf("[Client Manager] Messages sent: %d/sec, received: %d/sec \n", messagesClientSentCount, messagesClientReceivedCount);
		messagesClientSentCount = 0;
		messagesClientReceivedCount = 0;
	}
}

void dataSender(Client* client)
{
	printf("[Client Manager] start sending data\n");
	cout << client->ipAddress;
	Client_Connection connection(client_io_service, false, client->ipAddress);

	Client_Packet clientPacket = Client_Packet();

	clientPacket.addUint8(99);

	for(;;)
	{
		clientPacket.addUint8(55);
		clientPacket.addUint8(55);
		clientPacket.addUint8(56);
		clientPacket.addUint8(57);
		clientPacket.addUint8(58);
		clientPacket.addUint8(59);
		clientPacket.addUint8(60);
		clientPacket.addUint8(40);
		clientPacket.addUint8(61);
		clientPacket.addUint8(99);
		connection.sendPacket(clientPacket);
		
		messagesClientSentCount++;
		clientPacket.reset();

		boost::this_thread::sleep(boost::posix_time::milliseconds(999));
	}
}

void receiveDataFromClient(void)
{
	printf("[Client Manager] start reading data\n");

	Client_Connection connection(client_io_service, true, "");
	
	//Creating the buffer before the loop, otherwise it takes extremely much processing time
	boost::array<uint8_t, connection.PACKET_MAXSIZE> bufferArray = {};
	
	for(;;)
	{
		//Listen and return the client IP
		bufferArray.empty();

		string currentClientAddress = connection.read(bufferArray);
		
		messagesClientReceivedCount++;
		//Check if client exists, else create new client
		bool isNewClient = true;

		cout <<  currentClientAddress << ": " << "\n" ;

		for each(Client* client in clients)
		{
			if(client->ipAddress.compare(currentClientAddress) == 0)
			{
				isNewClient = false;
			}
		}

		if(isNewClient)
		{
			Client* newClient = new Client(currentClientAddress);
			clients.push_back(newClient);
			//TODO Is dit een kopie of niet??
			thread thread_send = thread(dataSender, newClient);
		}

		//TODO messages handlen
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
