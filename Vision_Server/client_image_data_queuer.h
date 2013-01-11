#ifndef CLIENT_IMAGE_DATA_QUEUER_H_
#define CLIENT_IMAGE_DATA_QUEUER_H_

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <vector>
#include <stdint.h>

#include <qmath.h>

#include "client.h"
#include "client_server_protocol.h"
#include "client_packet.h"

using namespace clientServerProtocol;
using namespace imageData;

class Client_Image_Data_Queuer : public QObject
{
	Q_OBJECT
public:
    explicit Client_Image_Data_Queuer(QObject *parent = 0);
public slots:
    void    handleImageData(QHostAddress clientAddress, uint8_t imgType, uint8_t imgStream, uint8_t strm);
signals:
    void noClientFound(QHostAddress*);
private:
    void	queueFrame(Client* client, uint8_t currentFrame, uint8_t imageType, uint8_t imageStream);
	Client* client;
    std::vector<uint8_t*> testImageData;
};
#endif /*CLIENT_IMAGE_DATA_QUEUER_H_*/
