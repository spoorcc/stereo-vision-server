#include "client.h"

Client::Client(std::string ip)
{
	ipAddress = ip;
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