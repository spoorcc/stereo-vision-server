#include "client_data_handler.h"

Client_Data_Handler::Client_Data_Handler(QObject *parent) : QObject(parent)
{

}

void Client_Data_Handler::processDatagram(QByteArray* bufferArray, QHostAddress clAddress)
{
    qDebug() << "[Client Manager] Data received, datatype:" << bufferArray->at(0) << ", Client ip:" << clAddress;
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
    case GET_FULL_XML:
    {
        emit newXMLRequest(clAddress);
        break;
    }
    case SET_PARAMETER:

        qDebug() << "[Client Manager] Set parameter " << QString(*bufferArray);
        break;
	default:
		printf("[Client Manager] Wrong datatype received! datatype: %d\n", bufferArray->at(0));
		break;
	}
}
