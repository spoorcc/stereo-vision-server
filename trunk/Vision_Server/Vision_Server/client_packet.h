#pragma comment(lib, "Ws2_32.lib")

#include <string>
#include <stdint.h>
#include <iostream>

class Client_Packet {
public:
	static const int Client_Packet::PACKET_MAXSIZE = 500;
	Client_Packet::Client_Packet(void);
	uint8_t* Client_Packet::getBuffer(void);
	void Client_Packet::reset(void);
	bool Client_Packet::canAdd(int);
	uint16_t Client_Packet::getMsgSize(void); 
	uint8_t Client_Packet::readUint8(void);	
	uint16_t Client_Packet::readUint16(void);
	bool Client_Packet::addUint8(uint8_t);		
	bool Client_Packet::addUint8(uint8_t*);	
	bool Client_Packet::addUint16(uint16_t);
private:
	uint16_t Client_Packet::readPos;
	uint16_t Client_Packet::MsgSize;
	uint8_t	Client_Packet::Buffer[Client_Packet::PACKET_MAXSIZE]; 
};