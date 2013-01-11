#include "client_image_data_queuer.h"

Client_Image_Data_Queuer::Client_Image_Data_Queuer(QObject *parent) : QObject(parent)
{

}

void Client_Image_Data_Queuer::handleImageData(QHostAddress clientAddress, uint8_t imgType, uint8_t imgStream, uint8_t stream)
{
    Client* client = findChild<Client*>(clientAddress.toString());

    if (client != NULL)
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
	//Send one full frame
    uint16_t totalSlices = (uint16_t) qCeil((double)testImageData.size() / imageData::MAX_SLICE_LENGTH);
	uint16_t lastSliceSize = testImageData.size() % imageData::MAX_SLICE_LENGTH;
			
	//When the lastSliceSize results zero, it actually means the data of the last slice is exactly 500 bytes
	if(lastSliceSize == 0)
	{
		lastSliceSize = imageData::MAX_SLICE_LENGTH;
	}
		
    for(uint16_t currentSlice = 0; currentSlice < totalSlices; currentSlice++)
	{
		uint16_t currentSliceSize = imageData::MAX_SLICE_LENGTH;
		//When last slice
		if(currentSlice == (totalSlices-1))
		{
			currentSliceSize = lastSliceSize;
		}

		int totalPacketSize = currentSliceSize + 10; //TODO counting the numbers of possible headers (byte 0 - 9)

		//Create new packet
        Client_Packet packet(this, totalPacketSize);

		//Beginning of protocol image data	
		packet.addUint8(IMAGE_DATA, DATATYPE);
		packet.addUint8(imageType, IMAGETYPE);	
		packet.addUint8(imageStream, STREAMID);
		packet.addUint8(currentFrame, FRAMEID);	
		packet.addUint16(currentSlice, SLICEINDEX_MSB);	
		packet.addUint16(totalSlices, TOTALSLICES_MSB);	
		packet.addUint16(currentSliceSize, SLICELENGTH_MSB); 

		//Add every char to the packet.

        //--------------------
        //TODO IMAGE DATA HERE
        //--------------------

		//Send packet and reset packet
		client->QueuePacket(&packet);
	}
}
