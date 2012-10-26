#include "client_packet.h"

using namespace std;

Client_Packet::Client_Packet(){
	reset();
}

void Client_Packet::reset(void) {
	MsgSize = 46;
	readPos = 46;
}

bool Client_Packet::canAdd(int _size) {
	return (_size+readPos < PACKET_MAXSIZE);
}

uint8_t* Client_Packet::getBuffer(void) {
	return Buffer;
}

uint16_t Client_Packet::getMsgSize(void) {
	return MsgSize;
}

//Read uint8 (1 byte) from to packet
uint8_t Client_Packet::readUint8(void) {
	uint8_t v = Buffer[readPos];
	readPos += 1;
	return v;
}

//Read uint16 (2 bytes) from to packet
uint16_t Client_Packet::readUint16(void) {
	uint16_t v = uint16_t(uint16_t(Buffer[readPos]) | (uint16_t(Buffer[readPos+1]) << 8));
	readPos += 2;
	return v;
}

//Add uint8 (1 byte) to packet
bool Client_Packet::addUint8(uint8_t _value) {
	if (canAdd(1) == false) {
		return false;
	}

	Buffer[readPos] = _value;
	readPos += 1;
	MsgSize += 1;

	return true;
}

//Add uint16 (2 bytes)  to packet
bool Client_Packet::addUint16(uint16_t _value) {
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