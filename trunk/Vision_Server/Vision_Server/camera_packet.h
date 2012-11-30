#include <string>
#include <stdint.h>
#include <iostream>

class Camera_Packet {
public:
	static const int Camera_Packet::PACKET_MAXSIZE = 1500;
	Camera_Packet::Camera_Packet(void);
	void Camera_Packet::newPacket(void); 
	uint8_t* Camera_Packet::getBuffer(void);
	void Camera_Packet::reset(void);
	bool Camera_Packet::canAdd(int);
	uint16_t Camera_Packet::getMsgSize(void); 
	uint8_t Camera_Packet::readUint8(void);	
	uint16_t Camera_Packet::readUint16(void);
	bool Camera_Packet::addUint8(uint8_t);		
	bool Camera_Packet::addUint16(uint16_t);
	void Camera_Packet::changeAllHeaders(uint8_t, uint16_t, bool);
	void Camera_Packet::changeRange(uint16_t);
	void Camera_Packet::setPacketLength(void);
private:
	uint16_t Camera_Packet::readPos;
	uint16_t Camera_Packet::MsgSize;
	uint8_t	Camera_Packet::Buffer[Camera_Packet::PACKET_MAXSIZE]; 
};