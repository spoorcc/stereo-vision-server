#pragma comment(lib, "Ws2_32.lib")

#include <stdint.h>
#include <iostream>
#include <WinSock2.h>

#include "packet.h"

using namespace std;

class Client_Connection {

public:
	Client_Connection(void); 
	void connectToClient(char*, int);
	int sendPacket(Packet);
	void listenToClients(void);
private:
	SOCKET sConnect;
	SOCKET slisten;
	SOCKADDR_IN addr;
	int addrlen;
	uint16_t readPos;
	uint16_t MsgSize;
	long answer;
};

