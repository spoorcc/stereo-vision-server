#ifndef CLIENT_DATA_HANDLER_H_
#define CLIENT_DATA_HANDLER_H_

#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <QString>
#include <QBuffer>
#include <QByteArray>

#include "client.h"
#include "client_data_queuer.h"

using namespace clientServerProtocol;
using namespace imageData;

class Client_Data_Handler : public QObject
{
	Q_OBJECT
public:
    explicit Client_Data_Handler(QObject *parent = 0);
    QByteArray getXML();
signals:
    void	newImageDataRequest(QHostAddress clientAddress, uint8_t imgType, uint8_t imgStream, uint8_t stream);
    void    newXMLRequest(QHostAddress clientAddress);
public slots:
    void processDatagram(QByteArray*, QHostAddress);
};
#endif /*CLIENT_DATA_HANDLER_H_*/
