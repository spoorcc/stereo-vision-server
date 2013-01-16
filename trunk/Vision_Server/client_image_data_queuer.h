#ifndef CLIENT_IMAGE_DATA_QUEUER_H_
#define CLIENT_IMAGE_DATA_QUEUER_H_

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <list>
#include <stdint.h>
#include <QImage>
#include <QBuffer>

#include <qmath.h>

#include "client.h"
#include "client_server_protocol.h"
#include "client_packet.h"
#include "graphics_manager.h"

using namespace clientServerProtocol;
using namespace imageData;

class Client_Image_Data_Queuer : public QObject
{
	Q_OBJECT
public:
    explicit Client_Image_Data_Queuer(std::list<Client*> *clList, Graphics_Manager* graphMan, QObject *parent = 0);
public slots:
    void    handleImageData(QHostAddress clientAddress, uint8_t imgType, uint8_t imgStream, uint8_t strm);
signals:
    void noClientFound(QHostAddress*);
private:
    Graphics_Manager* graphMan;
    std::list<Client*>* clientList;
    void	queueFrame(Client* client, uint8_t currentFrame, uint8_t imageType, uint8_t imageStream);
	Client* client;
};
#endif /*CLIENT_IMAGE_DATA_QUEUER_H_*/
