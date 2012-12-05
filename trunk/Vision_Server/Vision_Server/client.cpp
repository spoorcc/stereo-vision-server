#include "client.h"

Client::Client(std::string ip, int port)
{
	ipAddress = ip;
	remote_endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ip), port);
}

void Client::QueuePacket(Client_Packet* packet)
{
	Lock();
	buffer.push_back(packet);
	Unlock();
}

void Client::Lock(void)
{
	clientMutex.lock();
}

void Client::Unlock(void)
{
	clientMutex.unlock();
}