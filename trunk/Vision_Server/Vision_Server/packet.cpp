#include "packet.h"

using namespace std;

//typedef unsigned char     uint8_t;

// Create new packet with 1 byte header
void Packet::newPacket(uint8_t _header, uint16_t _range, bool _read) {
	reset();
	addUint8(_header);
	addUint16(_range);
	if(_read){
		//Read
		addUint8(0x0);
	}else{
		//Write
		addUint8(0x1);
	}
}

void Packet::changeAllHeaders(uint8_t _header, uint16_t _range, bool _read){
	//Header
	Buffer[0] = _header;

	//Range
	Buffer[1] = uint8_t(_range);
	Buffer[2] = uint8_t(_range >> 8);

	if(_read){
		//Read
		Buffer[3] = 0x00;
	}else{
		//Write
		Buffer[3] = 0x10;
	}
}

void Packet::changeRange(uint16_t _range)
{
	//Range
	Buffer[1] = uint8_t(_range);
	Buffer[2] = uint8_t(_range >> 8);
}

Packet::Packet()
{
	
}

void Packet::reset(void) {
	MsgSize = 0;
	readPos = 0;
}

bool Packet::canAdd(int _size) {
	return (_size+readPos < PACKET_MAXSIZE);
}

uint8_t* Packet::getBuffer(void) {
	return Buffer;
}

uint16_t Packet::getMsgSize(void) {
	return MsgSize;
}

//Read uint8 (1 byte) from to packet
uint8_t Packet::readUint8(void) {
	uint8_t v = Buffer[readPos];
	readPos += 1;
	return v;
}

//Read uint16 (2 bytes) from to packet
uint16_t Packet::readUint16(void) {
	uint16_t v = uint16_t(uint16_t(Buffer[readPos]) | (uint16_t(Buffer[readPos+1]) << 8));
	readPos += 2;
	return v;
}

//Add uint8 (1 byte) to packet
bool Packet::addUint8(uint8_t _value) {
	if (canAdd(1) == false) {
		return false;
	}

	Buffer[readPos] = _value;
	readPos += 1;
	MsgSize += 1;

	return true;
}

//Add uint16 (2 bytes)  to packet
bool Packet::addUint16(uint16_t _value) {
	if (canAdd(2) == false) {
		return false;
	}

	Buffer[readPos] = uint8_t(_value);
	readPos += 1;
	Buffer[readPos] = uint8_t(_value >> 8);
	readPos += 1;

	MsgSize += 2;

	return true;
}