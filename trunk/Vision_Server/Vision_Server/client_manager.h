#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include "client_connection.h"

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <vector>

using namespace boost; 
#define CLIENT_PORT 49679

class Client_Manager {
public:
			Client_Manager::Client_Manager(void);
	void	Client_Manager::startClientManager(void);
	void	Client_Manager::receiveDataFromClient(void);
	void	Client_Manager::dataSender(Client*);
	void	Client_Manager::calculateClientMessagesPerSecond(void);
	void	Client_Manager::handleData(std::vector<uint8_t>* bufferArray, string* clientAddress);
	void	Client_Manager::sendImageData(uint8_t, uint8_t, uint8_t, Client*);
	void	Client_Manager::sendFrame(uint8_t imageType, uint8_t imageStream, uint8_t currentFrame, Client* client);
	void	Client_Manager::fillListWithRandomData(std::vector<uint8_t*> dataList);
	Client* Client_Manager::getClient(string* clientAddress);
};
#endif