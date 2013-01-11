#include "client.h"

Client::Client(QObject *parent, QString ip, int port) : QObject(parent)
{
    Client_Data_Sender dataSender(this);

    dataSender.connectToClient(QHostAddress(ip), port);

    connect(this, SIGNAL(handleSendBuffer()), &dataSender, SLOT(handleSendBuffer()));
    connect(this, SIGNAL(newPacket(Client_Packet*)), &dataSender, SLOT(QueuePacket(Client_Packet*)));

    this->setObjectName(ip);
}

void Client::handleBuffer()
{
    emit handleSendBuffer();
}

void Client::Lock(void)
{
    //TODO
    //clientMutex.lock();
}

void Client::Unlock(void)
{
    //TODO
    //clientMutex.unlock();
}

QString Client::getIp()
{
	return ipAddress;
}

void Client::QueuePacket(Client_Packet* packet)
{
    emit newPacket(packet);
}
