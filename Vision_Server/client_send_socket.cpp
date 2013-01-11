#include "client_send_socket.h"

Client_Send_Socket::Client_Send_Socket(QObject *parent) :
    QUdpSocket(parent)
{

}

void Client_Send_Socket::connectToClient(QHostAddress hostAdress, quint16 port)
{
    //Close current connection
    close();

    //Try to connect
    connectToHost( hostAdress, port, QIODevice::WriteOnly );

    //Check if succes
    if( state() )
    {
        //printf("Connected succesfully to" + peerAddress().toString() + " on port " + QString::number( peerPort() ) );
        //emit connectionSucces();
    }
    else
    {
        printf("Connection failed");
        //emit connectionFailed();
    }
}

void Client_Send_Socket::writeDataToClient(Client_Packet* packet)
{
	write(*packet->getBuffer());
}
