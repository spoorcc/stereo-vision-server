#ifndef DATASENDSOCKET_H_
#define DATASENDSOCKET_H_

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <qmath.h>

#include "client_server_protocol.h"
#include "client_packet.h"

#define MAX_UDP_MESSAGE_SIZE 512

class Client_Send_Socket : public QUdpSocket
{
    Q_OBJECT
public:
    explicit Client_Send_Socket(QObject *parent = 0);
    
    void connectToClient(QHostAddress hostAdress, quint16 port); 
	void writeDataToClient(Client_Packet*);

private:
    QByteArray createDatagram(QString command);
};

#endif // DATASENDSOCKET_H_
