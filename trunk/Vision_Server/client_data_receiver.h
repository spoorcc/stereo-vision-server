#ifndef CLIENT_DATA_RECEIVER_H_
#define CLIENT_DATA_RECEIVER_H_

#include <QObject>
#include <vector>

#include "client_data_handler.h"
#include "client_receive_socket.h"

class Client_Data_Receiver : public QObject
{
	Q_OBJECT
public:
    explicit Client_Data_Receiver(QObject *parent = 0);
    Client_Receive_Socket* getConnection();
private:
	std::list<Client*>* clients;
    Client_Receive_Socket receiveConnection;
signals:
    void addReceived();
    void addReceivedCount();
};
#endif /*CLIENT_DATA_RECEIVER_H_*/
