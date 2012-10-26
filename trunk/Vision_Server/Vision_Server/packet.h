#pragma comment(lib, "Ws2_32.lib")

#include <string>
#include <stdint.h>
#include <iostream>

class Packet {
public:
	static const int Packet::PACKET_MAXSIZE = 1500;
	Packet::Packet(void);
	void Packet::newPacket(void); 
	uint8_t* Packet::getBuffer(void);
	void Packet::reset(void);
	bool Packet::canAdd(int);
	uint16_t Packet::getMsgSize(void); 
	uint8_t Packet::readUint8(void);	
	uint16_t Packet::readUint16(void);
	bool Packet::addUint8(uint8_t);		
	bool Packet::addUint16(uint16_t);
	void Packet::changeAllHeaders(uint8_t, uint16_t, bool);
	void Packet::changeRange(uint16_t);
	void Packet::setPacketLength(void);
private:
	uint16_t Packet::readPos;
	uint16_t Packet::MsgSize;
	uint8_t	Packet::Buffer[Packet::PACKET_MAXSIZE]; 
};