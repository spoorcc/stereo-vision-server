#include "client_receive_socket.h"

using namespace clientServerProtocol;

Client_Receive_Socket::Client_Receive_Socket(QObject *parent) : QUdpSocket(parent)
{
	listenToAllClients();

    connect(this, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

void Client_Receive_Socket::listenToAllClients()
{
	this->bind(DEFAULT_SERVER_PORT);
}

void Client_Receive_Socket::readPendingDatagrams()
{
    while ( hasPendingDatagrams() )
    {
        QByteArray* datagram = new QByteArray();
        datagram->resize( pendingDatagramSize() );
        QHostAddress sender;
        quint16 senderPort;

        readDatagram( datagram->data(), datagram->size(), &sender, &senderPort);

        emit newDataReceived(datagram, sender);
        emit addReceived();
    }
}
