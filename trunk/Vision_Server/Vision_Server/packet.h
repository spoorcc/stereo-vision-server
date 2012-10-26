#pragma comment(lib, "Ws2_32.lib")

#include <string>
#include <stdint.h>
#include <iostream>

class Packet {
public:
	static const int PACKET_MAXSIZE = 297;
	Packet(void);
	void newPacket(void); 
	uint8_t* getBuffer(void);
	void reset(void);
	bool canAdd(int);
	uint16_t getMsgSize(void); 
	uint8_t readUint8(void);	
	uint16_t readUint16(void);
	bool addUint8(uint8_t);		
	bool addUint16(uint16_t);
	void Packet::changeAllHeaders(uint8_t, uint16_t, bool);
	void Packet::changeRange(uint16_t);
private:
	uint16_t readPos;
	uint16_t MsgSize;
	uint8_t	Buffer[PACKET_MAXSIZE]; 
};