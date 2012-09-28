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
	Camera_Connection(void); 
	void sendPacket(Packet);
	boost::array<uint8_t, 1028> read();
	void setReadConnection(void);
private:
	uint16_t readPos;
	uint16_t MsgSize;
	long answer;

	//udp::socket socket;
	//udp::socket socket();
};

