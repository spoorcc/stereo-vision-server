#include "client_connection.h"

using namespace std;
using namespace boost;

boost::asio::io_service client_io_service;

Client_Connection::Client_Connection(int port) : socket_(client_io_service) 
{
	try{
		//Open send socket
		socket_.open(udp::v4());

		//Bind to the port
		local_endpoint = udp::endpoint(boost::asio::ip::address_v4::any(), port);
		socket_.bind(local_endpoint);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

bool Client_Connection::sendPacket(Client_Packet& packet, udp::endpoint remote_endpoint)
{
	try
	{
		socket_.send_to(boost::asio::buffer(packet.getBuffer()), remote_endpoint, 0, ignored_error);
		return true;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}
}

string Client_Connection::read(std::vector<uint8_t>& msg)
{
	try
	{
		udp::endpoint sender_endpoint;
		size_t len = socket_.receive_from(boost::asio::buffer(msg), sender_endpoint);
		string currentClient = sender_endpoint.address().to_v4().to_string();
		return currentClient;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return "";
}

