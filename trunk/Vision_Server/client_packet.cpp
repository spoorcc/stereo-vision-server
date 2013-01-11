#include "client_packet.h"

Client_Packet::Client_Packet(QObject *parent, int packet_size) : QObject(parent)
{
	Buffer.clear();
	Buffer.resize(packet_size);
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
	Buffer[pos] = value;
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
	Buffer[startPos] = uint8_t(value >> 8);
	Buffer[startPos+1] = uint8_t(value);

	return true;
}

QByteArray* Client_Packet::getBuffer(void)
{
	return &Buffer;
}
