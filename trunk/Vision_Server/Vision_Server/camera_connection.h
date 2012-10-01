#pragma comment(lib, "Ws2_32.lib")

#include <stdint.h>
#include <iostream>
#include <WinSock2.h>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "packet.h"

using namespace std;
using boost::asio::ip::udp;

class Camera_Connection {
public:
	Camera_Connection(boost::asio::io_service&, bool); 
	void sendPacket(Packet);
	boost::array<uint8_t, 1028> read();
	void setReadConnection(void);
private:
	uint16_t readPos;
	uint16_t MsgSize;
	long answer;
	udp::endpoint local_endpoint;
	udp::socket socket_;
	udp::endpoint remote_endpoint;
	boost::system::error_code ignored_error;
	udp::endpoint sender_endpoint;
};

