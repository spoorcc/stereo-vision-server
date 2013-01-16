#include "client_data_queuer.h"

Client_Data_Queuer::Client_Data_Queuer(std::list<Client*> *clList, Graphics_Manager* grMan, QObject *parent) : QObject(parent)
{
    clientList = clList;
    graphMan = grMan;
}

void Client_Data_Queuer::queueImageData(QHostAddress clientAddress, uint8_t imgType, uint8_t imgStream, uint8_t stream)
{
    qDebug() << "[Client Image Data Queuer] Handle Image Data, imgType:" << imgType << "Stream id:" << imgStream << "no singleShot:" << stream;

    Client* client = findClient(clientAddress);

    if (client == NULL)
    {
         qDebug() << "[Client Data Queuer] Unknown Client! Creating new client. Unable to handle current request, please retry.";
         emit noClientFound(&clientAddress);
         return;
    }

	if(stream != 0){
		//Endless Stream
        //TODO delete for loop
		for(;;)
		{
			//Endless loop sending frames
			for(int frame = 1; frame <= 50; frame++)
			{
                queueFrame(client, frame, imgType, imgStream);
			}

			//TODO break when client is disconnected
		}
	}
	else
	{
		//Single Shot
        queueFrame(client, 0x00, imgType, imgStream);
	}
}

void Client_Data_Queuer::queueFrame(Client* client, uint8_t currentFrame, uint8_t imageType, uint8_t imageStream)
{
    qDebug() << "[Client Data Queuer] Queue Frame";
	//Send one full frame

    //Create new packet
    Client_Packet packet(this);

    //Beginning of protocol image data
    packet.addUint8(IMAGE_DATA, DATATYPE);
    packet.addUint8(imageType, IMAGETYPE);
    packet.addUint8(imageStream, STREAMID);
    packet.addUint8(currentFrame, FRAMEID);

    //Add image data
    QByteArray* imgData;

    if(graphMan != NULL)
    {
        qDebug() << "[Client Data Queuer] Graphics pointer is NOT NULL";
        imgData = graphMan->getBuffer(imageStream);
    }
    else
    {
        qDebug() << "[Client Data Queuer] Graphics pointer is NULL";
    }

    qDebug() << "[Client Data Queuer] Image Size: " << imgData->size();

    packet.pushBack(imgData);

    qDebug() << "Image packet data: " << packet.getBuffer()->at(0) << "Size: " << packet.getBuffer()->size();

    //Send packet
    client->QueuePacket(&packet);
}

void Client_Data_Queuer::queueXML(QHostAddress clientAddress)
{
    qDebug() << "[Client Data Queuer] Handle Image Data";

    Client* client = findClient(clientAddress);

    if (client == NULL)
    {
         emit noClientFound(&clientAddress);
         qDebug() << "[Client Data Queuer] Unknown Client! Can't handle request yet.";
         return;
    }

    //XML
    QFile* file = new QFile("/home/nick/stereo-vision-server/ProcessSteps.xml");
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray* xmlFile = new QByteArray( file->readAll() );
    qDebug() << "[Client Data Queuer] Size of XML File: " << xmlFile->length();
    Client_Packet* packet = new Client_Packet(this);
    packet->addUint8(XML_FULL_CLIENT);

    packet->pushBack(xmlFile);
    client->QueuePacket(packet);

    return;
}

Client* Client_Data_Queuer::findClient(QHostAddress clientAddress)
{
    Client* client = NULL;

    foreach(Client* cl, *clientList)
    {
        if(cl->getHostAddress() == clientAddress)
        {
            client = cl;
        }
    }

    return client;
}
