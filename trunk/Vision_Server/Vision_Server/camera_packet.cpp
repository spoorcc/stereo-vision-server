#include "camera_packet.h"

using namespace std;

// Create new packet with 1 byte header
void Camera_Packet::newPacket(void) {
}

void Camera_Packet::changeAllHeaders(uint8_t _header, uint16_t _range, bool _read){
	//Header
	Buffer[42] = _header;

	//Range
	Buffer[43] = uint8_t(_range);
	Buffer[44] = uint8_t(_range >> 8);

	if(_read){
		//Read
		Buffer[45] = 0x00;
	}else{
		//Write
		Buffer[45] = 0x01;
	}
}

void Camera_Packet::changeRange(uint16_t _range)
{
	//Range
	Buffer[1] = uint8_t(_range);
	Buffer[2] = uint8_t(_range >> 8);
}

Camera_Packet::Camera_Packet(){
	reset();
	// set mac destination address to 01 : 01 : 01 : 01 : 01 : 01
		Buffer[0] = 0x01;
		Buffer[1] = 0x00;
		Buffer[2] = 0x5e;
		Buffer[3] = 0x00;
		Buffer[4] = 0x00;
		Buffer[5] = 0xfc;
    
    // set mac source address to 02 : 02 : 02 : 02 : 02 : 02
		Buffer[6]  = 0x14;
		Buffer[7]  = 0xfe;
		Buffer[8]  = 0xb5;
		Buffer[9]  = 0xbe;
		Buffer[10] = 0x6d;
		Buffer[11] = 0x09;
	
	// Ether Type
		Buffer[12] = 0x08;
		Buffer[13] = 0x00;

	// Version, header lenght, Differentiated Services, Total Length.
		Buffer[14]  = 0x45;
		Buffer[15]  = 0x00;
		Buffer[16]	= 0x01;
		Buffer[17]	= 0x20;

	// Identification, Flags , Fragment Offset
		Buffer[18]  = 0x05;
		Buffer[19]  = 0x42;
		Buffer[20]	= 0x00;
		Buffer[21]	= 0x00;

	// Time to Live
		Buffer[22]	= 0x01;
	// Protocol
		Buffer[23]	= 0x11;
	// Header Chechksum
		Buffer[24]	= 0x70;
		Buffer[25]	= 0x20;

	//Source Address
		Buffer[26]  = 0xA9;
		Buffer[27]  = 0xFE;
		Buffer[28]	= 0xB8;
		Buffer[29]	= 0x70;

	// Destination Adress
		Buffer[30]  = 0xE0;
		Buffer[31]  = 0x00;
		Buffer[32]	= 0x00;
		Buffer[33]	= 0xFC;

	// Source Port
		Buffer[34]	= 0xc3;
		Buffer[35]	= 0xb5;

	// Destination Port
		Buffer[36]	= 0x30;
		Buffer[37]	= 0x37;
	// Length
		Buffer[38]	= 0x01;
		Buffer[39]	= 0x0c;

	// Checksum
		Buffer[40]	= 0x2e;
		Buffer[41]	= 0xe4;
}

void Camera_Packet::reset(void) {
	MsgSize = 46;
	readPos = 46;
}

bool Camera_Packet::canAdd(int _size) {
	return (_size+readPos < PACKET_MAXSIZE);
}

uint8_t* Camera_Packet::getBuffer(void) {
	return Buffer;
}

uint16_t Camera_Packet::getMsgSize(void) {
	return MsgSize;
}

//Read uint8 (1 byte) from to packet
uint8_t Camera_Packet::readUint8(void) {
	uint8_t v = Buffer[readPos];
	readPos += 1;
	return v;
}

//Read uint16 (2 bytes) from to packet
uint16_t Camera_Packet::readUint16(void) {
	uint16_t v = uint16_t(uint16_t(Buffer[readPos]) | (uint16_t(Buffer[readPos+1]) << 8));
	readPos += 2;
	return v;
}

//Add uint8 (1 byte) to packet
bool Camera_Packet::addUint8(uint8_t _value) {
	if (canAdd(1) == false) {
		return false;
	}

	Buffer[readPos] = _value;
	readPos += 1;
	MsgSize += 1;

	return true;
}

//Add uint16 (2 bytes)  to packet
bool Camera_Packet::addUint16(uint16_t _value) {
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

void Camera_Packet::setPacketLength(void)
{
	// Lengt
	uint16_t tempMsgSize = MsgSize - 42;

	Buffer[38]	= uint8_t(tempMsgSize);
	Buffer[39]	= uint8_t(tempMsgSize >> 8);
}