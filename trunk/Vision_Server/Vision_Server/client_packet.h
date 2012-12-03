#include <stdint.h>
#include <iostream>
#include <vector>

class Client_Packet {
public:
	static const int Client_Packet::PACKET_MAXSIZE = 500;
	Client_Packet::Client_Packet(int packet_size);
	bool Client_Packet::canAdd(int size);
	uint16_t Client_Packet::getMsgSize(void); 
	uint8_t Client_Packet::readUint8(uint16_t pos);	
	uint16_t Client_Packet::readUint16(uint16_t pos);
	bool Client_Packet::addUint8(uint8_t);
	bool Client_Packet::addUint8(uint8_t value, uint16_t pos);
	bool Client_Packet::addUint16(uint16_t);
	bool Client_Packet::addUint16(uint16_t, uint16_t startPos);
	bool Client_Packet::addVector(std::vector<uint8_t*> *vec, int size, uint16_t startPos);
	std::vector<uint8_t> Client_Packet::getBuffer(void);
private:
	std::vector<uint8_t> Client_Packet::Buffer;
};