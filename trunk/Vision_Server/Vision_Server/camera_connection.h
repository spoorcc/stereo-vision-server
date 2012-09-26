#pragma comment(lib, "Ws2_32.lib")

#include <stdint.h>
#include <iostream>
#include <WinSock2.h>

#include "packet.h"

using namespace std;

class Camera_Connection {

public:
	Camera_Connection(void); 
	void connectToCamera(char*, int);
	int sendPacket(Packet);
private:
	SOCKET sconnect;
	SOCKADDR_IN addr;
	int addrlen;
	uint16_t readPos;
	uint16_t MsgSize;
};

