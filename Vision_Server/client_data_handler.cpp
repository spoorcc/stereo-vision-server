#include "client_data_handler.h"

Client_Data_Handler::Client_Data_Handler(QObject *parent) : QObject(parent)
{

}

void Client_Data_Handler::processDatagram(QByteArray* bufferArray, QHostAddress clAddress)
{
    printf("[Client Manager] Data received, datatype: %d\n", bufferArray->at(0));
	switch(bufferArray->at(0))
	{
	case GET_IMAGE:
		{
			uint8_t imageType = bufferArray->at(1);
			uint8_t stream = bufferArray->at(2);
			
            //TODO: only no stream at the moment
            emit newImageDataRequest(clAddress, imageType, stream, 0);

			break;
		}
	default:
		printf("[Client Manager] Wrong datatype received! datatype: %d\n", bufferArray->at(0));
		break;
	}
}
