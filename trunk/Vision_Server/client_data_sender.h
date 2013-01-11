#ifndef CLIENT_DATA_SENDER_H_
#define CLIENT_DATA_SENDER_H_

#include <QObject>
#include <deque>
#include "client_send_socket.h"

class Client_Data_Sender : public QObject
{
	Q_OBJECT
public:
    explicit Client_Data_Sender(QObject *parent = 0);
    bool sendPacket(Client_Packet* packet);
    void connectToClient(QHostAddress ip, int port);
signals:
	void addSentCount();
public slots:
    void QueuePacket(Client_Packet* packet);
    void	handleSendBuffer();
private:
    Client_Send_Socket connection;
    std::deque<Client_Packet*> buffer;
};
#endif /* CLIENT_DATA_SENDER_H_ */
