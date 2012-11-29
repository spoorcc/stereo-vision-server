#pragma comment(lib, "Ws2_32.lib")

#include <stdint.h>
#include <iostream>
#include <stdlib.h>
#include <deque>
#include <boost\thread\mutex.hpp>

#include "client_packet.h"
#include "client_server_protocol.h"

class Client
{
public:
	Client::Client(std::string);
	void Client::QueuePacket(Client_Packet* packet);
	std::string ipAddress;
	std::deque<Client_Packet> buffer;
	void Client::Lock(void);
	void Client::Unlock(void);
private:
	boost::mutex clientMutex;
};