#include "client_manager.h"

Client_Manager::Client_Manager(QObject *parent) : QObject(parent)
{
	printf("[Client Manager] Client Manager started.\n");

    imgDataQueuer = new Client_Image_Data_Queuer(&clients, this);

    this->connect(imgDataQueuer, SIGNAL( noClientFound(QHostAddress*) ), this, SLOT( createNewClient(QHostAddress*) ));

    msgCounter = new Message_Counter(this);
    msgCounter->connect(&dataReceiver, SIGNAL( addReceivedCount() ), SLOT( countReceivedUp() ));

    imgDataQueuer->connect(&clientDataHandler, SIGNAL( newImageDataRequest(QHostAddress,uint8_t,uint8_t,uint8_t) ), SLOT( handleImageData(QHostAddress,uint8_t,uint8_t,uint8_t) ));
    clientDataHandler.connect(dataReceiver.getConnection(), SIGNAL( newDataReceived(QByteArray*, QHostAddress) ), SLOT( processDatagram(QByteArray*, QHostAddress) ) );
}

void Client_Manager::fillListWithRandomData(std::vector<uint8_t*> dataList)
{
	for(uint16_t i = 0; i < dataList.size(); i++)
	{
		//dataList.at(i) = new uint8_t(std::rand() % 256);
		dataList.at(i) = new uint8_t(i);
	}
}

void Client_Manager::createNewClient(QHostAddress* clientAddress)
{
	//Check if client exists, else create new client
    foreach(Client* client, clients)
	{
        if(client->getIp().compare((*clientAddress).toString()) == 0)
		{
            qDebug() << "[Client Manager] Error: Client already made";
            return;
		}
	}

    qDebug() << "[Client Manager] Creating new client";
    Client* newClient = new Client(this, *clientAddress, CLIENT_PORT);

	clients.push_back(newClient);

	//TODO Fix the msgCounter
    msgCounter->connect(newClient->getSender(), SIGNAL(addSentCount()), SLOT(countSendUp()));

    return;
}
