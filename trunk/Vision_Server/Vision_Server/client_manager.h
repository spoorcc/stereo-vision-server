#pragma comment(lib, "Ws2_32.lib")
#include "client_connection.h"

using namespace boost; 

Client_Connection connection(boost::asio::io_service&);

boost::asio::io_service client_io_service;

void startClientManager(void);
void receiveDataFromClient(void);
void sendDataToClient(void);

void calculateClientMessagesPerSecond(void);