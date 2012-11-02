#pragma comment(lib, "Ws2_32.lib")

#include <string>
#include <stdint.h>
#include <iostream>

class Camera_packet {
public:
	static const int Camera_packet::PACKET_MAXSIZE = 1500;
	Camera_packet::Camera_packet(void);
	void Camera_packet::newPacket(void); 
	uint8_t* Camera_packet::getBuffer(void);
	void Camera_packet::reset(void);
	bool Camera_packet::canAdd(int);
	uint16_t Camera_packet::getMsgSize(void); 
	uint8_t Camera_packet::readUint8(void);	
	uint16_t Camera_packet::readUint16(void);
	bool Camera_packet::addUint8(uint8_t);		
	bool Camera_packet::addUint16(uint16_t);
	void Camera_packet::changeAllHeaders(uint8_t, uint16_t, bool);
	void Camera_packet::changeRange(uint16_t);
	void Camera_packet::setPacketLength(void);
private:
	uint16_t Camera_packet::readPos;
	uint16_t Camera_packet::MsgSize;
	uint8_t	Camera_packet::Buffer[Camera_packet::PACKET_MAXSIZE]; 
};