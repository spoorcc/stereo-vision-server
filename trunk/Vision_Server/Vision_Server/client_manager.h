#include "client_connection.h"
#include <boost\thread.hpp>
#include <vector>

using namespace boost; 

Client_Connection connection(boost::asio::io_service&);

boost::asio::io_service client_io_service;

void startClientManager(void);
void receiveDataFromClient(void);
void dataSender(Client*);

void calculateClientMessagesPerSecond(void);

void handleData(std::vector<uint8_t>* bufferArray, string* clientAddress);
void sendImageData(uint8_t, uint8_t, uint8_t, Client*);
void sendFrame(uint8_t imageType, uint8_t imageStream, uint8_t currentFrame, Client* client);

void fillListWithRandomData(std::vector<uint8_t*> dataList);

Client* getClient(string* clientAddress);