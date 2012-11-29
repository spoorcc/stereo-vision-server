#include "includes.h"
#include "client_manager.h"

uint32_t messagesClientReceivedCount = 0;
uint32_t messagesClientSentCount = 0;

std::list<Client*> clients;
std::list<uint8_t*> testImageData;

void startClientManager(void)
{
	//TODO
	printf("[Client Manager] Client Manager started.\n");
	
	fillListWithRandomData(testImageData);
	printf("[Client Manager] Image data filled with random data.\n");

	thread thread_receive = thread(receiveDataFromClient);
	thread thread_calc = thread(calculateClientMessagesPerSecond);

	for(;;)
	{
		//Don't close the client manager
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000)); 
	}
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
			//Send packets and pop the first one
			client->Lock();
			connection.sendPacket(client->buffer.front());
			client->buffer.pop_front();
			client->Unlock();
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
			thread thread_handleImages = thread(sendImageData, imageType, stream, bufferArray->at(3), client);
			break;
		}
	default:
		printf("Wrong datatype received!\n");
		break;
	}
}

void sendImageData(uint8_t imageType, uint8_t imageStream, uint8_t stream, Client* client)
{
	if(stream == true){
		//Endless Stream
		for(;;)
		{
			//Endless loop sending frames
			for(int frame = 1; frame <= 50; frame++)
			{
				sendFrame(imageType, imageStream, frame, client);
			}
		}
	}
	else
	{
		//Single Shot
		sendFrame(imageType, imageStream, 0x00, client);
	}
}

void sendFrame(uint8_t imageType, uint8_t imageStream, uint8_t currentFrame, Client* client)
{
	Client_Packet packet = Client_Packet();

	//Send one full frame
	uint16_t count = 1;
	uint16_t totalSlices = ceil((double)testImageData.size() / 500);
	uint16_t lastSliceSize = testImageData.size() % 500;
			
	//When the lastSliceSize results zero, it actually means the data of the last slice is exactly 500 bytes
	if(lastSliceSize == 0)
	{
		lastSliceSize = 500;
	}
		
	for each(uint8_t *val in testImageData)
	{

		if(packet.getMsgSize() == 0)
		{
			//Beginning of protocol image data
			//TODO Cast enum to int for clientDataTypes
			packet.addUint8(0x50);			//Byte 1	(Datatype)
			packet.addUint8(imageType);		//Byte 2	(Image Type)
			packet.addUint8(imageStream);	//Byte 3	(Stream ID)
			packet.addUint8(currentFrame);			//Byte 4	(Current Frame)
			packet.addUint16(count);		//Byte 5+6	(Current Slice)
			packet.addUint16(totalSlices);	//Byte 7+8	(Total Slices)
					
			//When last slice
			if(count == totalSlices)
			{
				packet.addUint16(lastSliceSize); //Byte 9+10 (Current Slice Length)
			}
			else
			{
				packet.addUint16(500);		//Byte 9+10 (Current Slice Length)
			}
		}
		//Add every char to the packet.
		packet.addUint8(*val);				// Byte 11-500	(Data)

		//Check if packet full
		if(packet.getMsgSize() == 500)
		{
			//Send packet and reset packet
			client->QueuePacket(&packet);
			packet = Client_Packet();
			count++;
		}
	}

	if(packet.getMsgSize() > 0)
	{
		//Send last packet
		client->QueuePacket(&packet);
	}	
}

void fillListWithRandomData(std::list<uint8_t*> dataList)
{
	for(int i = 0; i < 3000; i++)
	{
		dataList.push_back(new uint8_t(std::rand() % 256));
	}
}
