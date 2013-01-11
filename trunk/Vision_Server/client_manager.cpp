#include "client_manager.h"

Client_Manager::Client_Manager(QObject *parent) : QObject(parent)
{
	printf("[Client Manager] Client Manager started.\n");

    this->connect(&imgDataQueuer, SIGNAL(noClientFound(QHostAddress*)), this, SLOT(createNewClient(QHostAddress*)));

    msgCounter.connect(&dataReceiver, SIGNAL(addReceivedCount()), &msgCounter, SLOT(countReceivedUp()));
    msgCounter.connect(this, SIGNAL(updateCount()), SLOT(printMessages()));

    clientDataHandler.connect(dataReceiver.getConnection(), SIGNAL( newDataReceived(QByteArray*, QHostAddress) ), &clientDataHandler, SLOT( processDatagram(QByteArray*, QHostAddress) ) );
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

    Client* newClient = new Client(this, (*clientAddress).toString(), CLIENT_PORT);

	clients.push_back(newClient);

	//TODO Fix the msgCounter
    //msgCounter.connect(&clientDataSender, SIGNAL(addSentCount()), SLOT(addSentCount()));

    return;
}
