#ifndef CLIENT_H_
#define CLIENT_H_

#include "client_server_protocol.h"
#include "client_packet.h"

#include <QObject>
#include <stdint.h>
#include <iostream>
#include <stdlib.h>
#include <deque>
#include <qstring.h>
#include <qqueue.h>

#include "client_send_socket.h"
#include "client_data_sender.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent, QString ip, int port);
	//Functions
	void Lock(void);
	void Unlock(void);
    QString getIp(void);
    void QueuePacket(Client_Packet*);
public slots:
    void handleBuffer();
private:
	QString ipAddress;
signals:
    void    handleSendBuffer();
    void    newPacket(Client_Packet*);
};
#endif
