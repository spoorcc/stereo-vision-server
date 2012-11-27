#include "includes.h"
#include "client_manager.h"

uint32_t messagesClientReceivedCount = 0;
uint32_t messagesClientSentCount = 0;

std::list<Client*> clients;

std::list<uint8_t*> testImageData;

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

	for(;;)
	{
		if(client->buffer.size() > 0)
		{
			//TODO Mutex?????
			//Send packets and pop the first one
			connection.sendPacket(client->buffer.front());
			client->buffer.pop_front();
			messagesClientSentCount++;
		}
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

		cout << currentClientAddress << ": " << "\n" ;

		Client* currentClient = NULL;
		for each(Client* client in clients)
		{
			if(client->ipAddress.compare(currentClientAddress) == 0)
			{
				isNewClient = false;
				currentClient = client;
			}
		}

		if(isNewClient)
		{
			Client* newClient = new Client(currentClientAddress);
			clients.push_back(newClient);
			thread thread_send = thread(dataSender, newClient);
			currentClient = newClient;
		}

		//TODO incoming data handlen in andere thread
		handleData(&bufferArray, currentClient);
	}
}

void handleData(boost::array<uint8_t, Client_Connection::PACKET_MAXSIZE>* bufferArray, Client* client)
{
	switch(bufferArray->at(0))
	{
	case GET_IMAGE:
		{
			uint8_t imageType = bufferArray->at(1);
			uint8_t stream = bufferArray->at(2);
			thread thread_handleImages = thread(streamImageData, bufferArray->at(1), bufferArray->at(2), bufferArray->at(3), client);
			break;
		}
	default:
		printf("Wrong datatype received");
		break;
	}
}

void streamImageData(uint8_t imageType, uint8_t imageStream, uint8_t stream, Client* client)
{
	for(;;)
	{
		//Send one full frame
		switch(imageType)
		{
		case JPEG:
			{
				Client_Packet packet = Client_Packet();
				int count = 0;

				for each(uint8_t *val in testImageData)
				{
					//TODO 
					//TODO
					if(packet.getMsgSize() == 0)
					{
						//TODO the rest of the data (Protocol)

					}
					packet.addUint8(val);
					if(packet.getMsgSize() == 500)
					{
						//Send packet
						client->buffer.push_back(packet);
					}
				}

				if(count > 0)
				{
					//Last msg
					client->buffer.push_back(packet);
				}
				
				break;
			}
		case RAW:
			{
				
				break;
			}
		default:
			printf("Wrong imageType received");
			break;
		}
		if(stream == 0)
		{
			return;
		}
	}
}

