#include "client_manager.h"

uint32_t messagesClientReceivedCount = 0;
uint32_t messagesClientSentCount = 0;

std::list<Client*> clients;
std::vector<uint8_t*> testImageData;

using namespace clientServerProtocol;
using namespace imageData;
using namespace std;

void startClientManager(void)
{
	//TODO
	printf("[Client Manager] Client Manager started.\n");
	testImageData.resize(10000);
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
			connection.sendPacket(*client->buffer.front());
			client->buffer.pop_front();
			client->Unlock();
			messagesClientSentCount++;
		}
	}
}

void receiveDataFromClient(void)
{
	printf("[Client Manager] Start receiving data...\n");

	Client_Connection connection(client_io_service, true, "");
	
	//Creating the buffer before the loop, otherwise it takes extremely much processing time
	std::vector<uint8_t> bufferArray (500);
	
	for(;;)
	{
		//Clear and reassign 500 bytes
		bufferArray.assign(500, NULL);

		//Listen and return the client IP
		string currentClientAddress = connection.read(bufferArray);
		
		
		messagesClientReceivedCount++;
		

		//TODO Check speed for creating this thread, maybe make a queue?
		boost::thread handleDataThread = thread(handleData, &bufferArray, &currentClientAddress);
	}
}

void handleData(std::vector<uint8_t>* bufferArray, string* clientAddress)
{
	//TODO Printf
	cout << *clientAddress << ": " << "\n" ;
	
	Client* client = getClient(clientAddress);
	
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
		printf("[Client Manager] Wrong datatype received! datatype: %d\n", bufferArray->at(0));
		break;
	}
}

Client* getClient(string* clientAddress)
{
	//Check if client exists, else create new client
	for each(Client* client in clients)
	{
		if(client->ipAddress.compare(*clientAddress) == 0)
		{
			return client;
		}
	}

	Client* newClient = new Client(*clientAddress);
	clients.push_back(newClient);
	boost::thread thread_send = thread(dataSender, newClient);

	return newClient;
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

			//TODO break when client is disconnected
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
	

	//Send one full frame
	uint16_t currentSlice = 1;
	uint16_t totalSlices = ceil((double)testImageData.size() / imageData::MAX_SLICE_LENGTH);
	uint16_t lastSliceSize = testImageData.size() % imageData::MAX_SLICE_LENGTH;
			
	//When the lastSliceSize results zero, it actually means the data of the last slice is exactly 500 bytes
	if(lastSliceSize == 0)
	{
		lastSliceSize = imageData::MAX_SLICE_LENGTH;
	}
		
	for(int currentSlice = 0; currentSlice < totalSlices; currentSlice++)
	{
		uint16_t currentSliceSize = imageData::MAX_SLICE_LENGTH;
		//When last slice
		if(currentSlice == (totalSlices-1))
		{
			currentSliceSize = lastSliceSize;
		}

		int totalPacketSize = currentSliceSize + 10; //TODO counting the numbers of possible headers (byte 0 - 9)

		//Create new packet
		Client_Packet packet = Client_Packet(totalPacketSize);

		//Beginning of protocol image data	
		packet.addUint8(IMAGE_DATA, DATATYPE);
		packet.addUint8(imageType, IMAGETYPE);	
		packet.addUint8(imageStream, STREAMID);
		packet.addUint8(currentFrame, FRAMEID);	
		packet.addUint16(currentSlice, SLICEINDEX_MSB);	
		packet.addUint16(totalSlices, TOTALSLICES_MSB);	
		packet.addUint16(currentSliceSize, SLICELENGTH_MSB); 

		//Add every char to the packet.
		packet.addVector(&testImageData, currentSliceSize, 10);

		//Send packet and reset packet
		//TODO copy packet to buffer
		client->QueuePacket(&packet);
	}
}

void fillListWithRandomData(std::vector<uint8_t*> dataList)
{
	for(uint16_t i = 0; i < dataList.size(); i++)
	{
		//dataList.at(i) = new uint8_t(std::rand() % 256);
		dataList.at(i) = new uint8_t(i);
	}
}
