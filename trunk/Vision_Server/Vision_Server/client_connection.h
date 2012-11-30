#include <stdint.h>
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "client.h"

using namespace std;
using boost::asio::ip::udp;

class Client_Connection {
public:
	static const int	Client_Connection::PACKET_MAXSIZE = 500;
	Client_Connection::Client_Connection(boost::asio::io_service&, bool, string); 
	void				Client_Connection::sendPacket(Client_Packet&);
	string				Client_Connection::read(std::vector<uint8_t>& msg);
	void				Client_Connection::setReadConnection(void);
private:
	uint16_t					Client_Connection::readPos;
	uint16_t					Client_Connection::MsgSize;
	long						Client_Connection::answer;
	udp::endpoint				Client_Connection::local_endpoint;
	udp::socket					Client_Connection::socket_;
	udp::endpoint				Client_Connection::remote_endpoint;
	boost::system::error_code	Client_Connection::ignored_error;
};

