#include "client_data_sender.h"

Client_Data_Sender::Client_Data_Sender(QObject *parent) : QObject(parent)
{

}

void Client_Data_Sender::connectToClient(QHostAddress ip, int port)
{
    connection.connectToClient(ip, port);
}

void Client_Data_Sender::handleSendBuffer()
{
    printf("[Client Manager] start sending data\n");
	//cout << client->ipAddress;

    while(buffer.empty() == false)
    {
        //Send packets and pop the first one
        if(sendPacket(buffer.front()) == true)
        {
            buffer.pop_front();
            emit addSentCount();
        }
    }
}

void Client_Data_Sender::QueuePacket(Client_Packet* packet)
{
    buffer.push_back(packet);
}

bool Client_Data_Sender::sendPacket(Client_Packet* packet)
{
    qDebug() << "[Client Data Sender] Start sending packet";
	try
	{
        connection.writeDataToClient(packet);
        qDebug() << "[Client Data Sender] Packet sent";
		return true;
	}
	catch (std::exception& e)
	{
        qDebug() << e.what();
		return false;
	}
}
