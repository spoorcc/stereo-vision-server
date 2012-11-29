#include "client.h"

Client::Client(std::string ip)
{
	ipAddress = ip;

}

void Client::QueuePacket(Client_Packet* packet)
{
	buffer.push_back(*packet);
}