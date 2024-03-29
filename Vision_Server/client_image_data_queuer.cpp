#include "client_image_data_queuer.h"

Client_Image_Data_Queuer::Client_Image_Data_Queuer(std::list<Client*> *clList, Graphics_Manager* grMan, QObject *parent) : QObject(parent)
{
    clientList = clList;
    graphMan = grMan;
}

void Client_Image_Data_Queuer::handleImageData(QHostAddress clientAddress, uint8_t imgType, uint8_t imgStream, uint8_t stream)
{
    qDebug() << "[Client Image Data Queuer] Handle Image Data";

    Client* client = NULL;

    foreach(Client* cl, *clientList)
    {
        qDebug() << cl->getIp();
        if(cl->getHostAddress() == clientAddress)
        {
            client = cl;
        }
    }

    if (client == NULL)
    {
         emit noClientFound(&clientAddress);
         qDebug() << "[Client_Image_Data_Queuer] Unknown Client! Can't handle request yet.";
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

void Client_Image_Data_Queuer::queueFrame(Client* client, uint8_t currentFrame, uint8_t imageType, uint8_t imageStream)
{
    qDebug() << "[Client Image Data Queuer] queueFrame!";
	//Send one full frame

    //Create new packet
    Client_Packet packet(this);

    //Beginning of protocol image data
    packet.addUint8(IMAGE_DATA, DATATYPE);
    packet.addUint8(imageType, IMAGETYPE);
    packet.addUint8(imageStream, STREAMID);
    packet.addUint8(currentFrame, FRAMEID);

    //Add every char to the packet.


    //TODO imgData is in Graphics Manager
    QByteArray* imgData = graphMan->getBuffer(0);
    qDebug() << "Image Size: " << imgData->size();

    packet.pushBack(imgData);

    //Send packet and reset packet
    client->QueuePacket(&packet);
}
