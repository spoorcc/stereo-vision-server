#include "client_data_handler.h"

Client_Data_Handler::Client_Data_Handler(QObject *parent) : QObject(parent)
{

}

void Client_Data_Handler::processDatagram(QByteArray* bufferArray, QHostAddress clAddress)
{
	switch(bufferArray->at(0))
	{
	case GET_IMAGE:
		{
			uint8_t imageType = bufferArray->at(1);
			uint8_t stream = bufferArray->at(2);
			


			break;
		}
	default:
		printf("[Client Manager] Wrong datatype received! datatype: %d\n", bufferArray->at(0));
		break;
	}
}
