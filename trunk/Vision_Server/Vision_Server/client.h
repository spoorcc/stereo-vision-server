#ifndef CLIENT_H
#define CLIENT_H

#include "client_server_protocol.h"
#include "client_packet.h"

#include <stdint.h>
#include <iostream>
#include <stdlib.h>
#include <deque>
#include <boost\thread\mutex.hpp>
#include <boost/asio.hpp>


class Client
{
public:
	Client::Client(std::string ip, int port);
	//Functions
	void Client::QueuePacket(Client_Packet* packet);
	void Client::Lock(void);
	void Client::Unlock(void);
	//Variables
	boost::asio::ip::udp::endpoint remote_endpoint;
	std::string ipAddress;
	std::deque<Client_Packet*> buffer;
private:
	boost::mutex clientMutex;
};
#endif