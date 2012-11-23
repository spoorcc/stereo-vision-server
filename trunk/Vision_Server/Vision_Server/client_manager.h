#pragma comment(lib, "Ws2_32.lib")
#include "client_connection.h"

using namespace boost; 

Client_Connection connection(boost::asio::io_service&);

boost::asio::io_service client_io_service;

void startClientManager(void);
void receiveDataFromClient(void);
void dataSender(Client*);

void calculateClientMessagesPerSecond(void);

void handleData(boost::array<uint8_t, Client_Connection::PACKET_MAXSIZE>* bufferArray, Client* client);
void streamImageData(uint8_t, uint8_t, uint8_t, Client*);