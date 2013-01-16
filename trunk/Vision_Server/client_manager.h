#ifndef CLIENT_MANAGER_H_
#define CLIENT_MANAGER_H_

#include "client_data_receiver.h"
#include "message_counter.h"
#include "client_server_protocol.h"
#include "client_data_sender.h"
#include "client_data_queuer.h"
#include "graphics_manager.h"

#include <QTimer>
#include <QDebug>
#include <vector>

#define CLIENT_PORT 49679

class Client_Manager : public QObject
{
	Q_OBJECT
public:
    explicit Client_Manager(Graphics_Manager* graphMan, QObject *parent = 0);
public slots: 
    void	createNewClient(QHostAddress*);
signals: 
	void	clientList(std::list<Client*>);
	void	msgTimerTimeout();
	void	clientInformation(Client*);
    void    updateCount();
    void    newXMLRequest(QHostAddress);
private:
    Message_Counter*         msgCounter;
    Client_Data_Receiver    dataReceiver;
    Client_Data_Queuer* dataQueuer;
    Client_Data_Handler     clientDataHandler;
	void	receiveDataFromClient(void);
	void	handleData(std::vector<uint8_t>* bufferArray, QString* clientAddress);
	void	sendImageData(uint8_t, uint8_t, uint8_t, Client*);
	void	sendFrame(uint8_t imageType, uint8_t imageStream, uint8_t currentFrame, Client* client);
	void	fillListWithRandomData(std::vector<uint8_t*> dataList);
	std::list<Client*> clients;
	
};
#endif /* CLIENT_MANAGER_H_ */
