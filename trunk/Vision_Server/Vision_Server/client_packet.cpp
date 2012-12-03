#include "client_packet.h"

using namespace std;

Client_Packet::Client_Packet(int packet_size)
{
	Buffer.clear();
	Buffer.resize(packet_size, 0);
}

bool Client_Packet::canAdd(int size) 
{
	return (size+Buffer.size() < PACKET_MAXSIZE);
}

uint16_t Client_Packet::getMsgSize(void) 
{
	return Buffer.size();
}

uint8_t Client_Packet::readUint8(uint16_t pos)
{
	return Buffer[pos];
}

//Read uint16 (2 bytes) from to packet
uint16_t Client_Packet::readUint16(uint16_t pos) 
{
	uint16_t v = uint16_t((uint16_t(Buffer[pos+1]) << 8) | uint16_t(Buffer[pos]));
	return v;
}

//Add uint8 (1 byte) to packet
bool Client_Packet::addUint8(uint8_t value) 
{
	if (canAdd(1) == false) 
	{
		return false;
	}
	Buffer.push_back(value);
	return true;
}

//Add uint8 (1 byte) to packet
bool Client_Packet::addUint8(uint8_t value, uint16_t pos) 
{
	Buffer.at(pos) = value;
	return true;
}

//Add uint16 (2 bytes)  to packet
bool Client_Packet::addUint16(uint16_t value) 
{
	if (canAdd(2) == false) 
	{
		return false;
	}

	Buffer.push_back(uint8_t(value));
	Buffer.push_back(uint8_t(value >> 8));

	return true;
}

//Add uint16 (2 bytes)  to packet
bool Client_Packet::addUint16(uint16_t value, uint16_t startPos) 
{
	Buffer.at(startPos) = uint8_t(value >> 8);
	Buffer.at(startPos+1) = uint8_t(value);

	return true;
}

bool Client_Packet::addVector(std::vector<uint8_t*> *vec, int size, uint16_t startPos)
{
	//TODO check buffer sizes
	/*if(Buffer.size() + size >= Buffer.max_size())
	{
		printf("Vector length: %d, Buffer length: %d\n", (*vec).size(), Buffer.size());
		return false;
	}*/
	memcpy(&Buffer[startPos] , &vec, size);
	
	return true;
}

std::vector<uint8_t> Client_Packet::getBuffer(void)
{
	return Buffer;
}