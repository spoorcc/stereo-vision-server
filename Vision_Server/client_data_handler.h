#ifndef CLIENT_DATA_HANDLER_H_
#define CLIENT_DATA_HANDLER_H_

#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <qstring.h>
#include <qthread.h>
#include <qobject.h>
#include <qbuffer.h>

#include "client.h"
#include "client_image_data_queuer.h"

using namespace clientServerProtocol;
using namespace imageData;

class Client_Data_Handler : public QObject
{
	Q_OBJECT
public:
    explicit Client_Data_Handler(QObject *parent = 0);
signals:
    void	newImageDataRequest(QHostAddress clientAddress, uint8_t imgType, uint8_t imgStream, uint8_t stream);
public slots:
    void processDatagram(QByteArray*, QHostAddress);
};
#endif /*CLIENT_DATA_HANDLER_H_*/
