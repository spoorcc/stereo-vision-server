#include "client.h"

Client::Client(QObject *parent, QHostAddress hostAddr, int port) : QObject(parent)
{
    hostAddress = hostAddr;
    \
    dataSender = new Client_Data_Sender(this);
    dataSender->connectToClient(getHostAddress(), port);

    connect(this, SIGNAL(handleSendBuffer()), dataSender, SLOT(handleSendBuffer()));
    connect(this, SIGNAL(newPacket(Client_Packet*)), dataSender, SLOT(QueuePacket(Client_Packet*)));
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
    return hostAddress.toString();
}

QHostAddress Client::getHostAddress(void)
{
    return hostAddress;
}

void Client::QueuePacket(Client_Packet* packet)
{
    qDebug() << "[Client] Queue Packet";
    emit newPacket(packet);
    emit handleSendBuffer();
}

Client_Data_Sender* Client::getSender(void)
{
    return dataSender;
}
