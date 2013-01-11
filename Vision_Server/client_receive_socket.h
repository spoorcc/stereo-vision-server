#ifndef CLIENT_RECEIVE_SOCKET_H_
#define CLIENT_RECEIVE_SOCKET_H_

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <vector>

#include "client.h"
#include "client_server_protocol.h"

class Client_Receive_Socket : public QUdpSocket
{
	Q_OBJECT
public:
	explicit Client_Receive_Socket(QObject *parent = 0);
signals:
    void	addReceived();
    void    newDataReceived(QByteArray*, QHostAddress);
private slots:
    void	readPendingDatagrams();
private:
	void	listenToAllClients();
};
#endif /*CLIENT_RECEIVE_SOCKET_H_*/
