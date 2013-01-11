#include "client_data_receiver.h"

Client_Data_Receiver::Client_Data_Receiver(QObject *parent) : QObject(parent)
{
    printf("[Client Manager] Start receiving data...\n");

    this->connect(&receiveConnection, SIGNAL( addReceived() ), this, SIGNAL( addReceivedCount() ));
}


Client_Receive_Socket* Client_Data_Receiver::getConnection()
{
    return &receiveConnection;
}
