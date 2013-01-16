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
        qDebug() << "[Client Send Socket] Connected succesfully to" << hostAdress.toString() << " on port " << port;
        //emit connectionSucces();
    }
    else
    {
        printf("[Client Send Socket] Connection failed");
        //emit connectionFailed();
    }
}

void Client_Send_Socket::writeDataToClient(Client_Packet* packet)
{
    int done = 0;
    u_int32_t count = 0;
    int msgLength = packet->getBuffer()->size();
    u_int32_t packetCount = qCeil( ((double) msgLength) / MAX_UDP_MESSAGE_SIZE);
    qDebug() << "[Client Send Socket] Total length: " << msgLength;

    if(packetCount > 1)
    {
        qDebug() << "[Client Send Socket] Splitting packets to " << packetCount << " packets.";
        QByteArray msgLengthPacket;
        msgLengthPacket.append(0xFF);
        msgLengthPacket.append(u_int8_t(packetCount));
        msgLengthPacket.append(u_int8_t(packetCount >> 8));
        msgLengthPacket.append(u_int8_t(packetCount >> 16));
        msgLengthPacket.append(u_int8_t(packetCount >> 24));

        //Write the amount of packets first
        write(msgLengthPacket);

        for(count = 0; count < packetCount; count++)
        {
            waitForBytesWritten(1000);

            done = write(packet->getBuffer()->mid(count * MAX_UDP_MESSAGE_SIZE, MAX_UDP_MESSAGE_SIZE));
            if(done == -1)
            {
                qDebug() << "Error sending";
            }
        }
    }
    else
    {
        waitForBytesWritten(1000);
        write(*packet->getBuffer());
    }
    qDebug() << "[Client Send Socket] Finished sending data";
}
