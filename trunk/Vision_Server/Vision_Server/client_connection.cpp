#include "client_connection.h"

#define Client_port 49679

using namespace std;

Client_Connection::Client_Connection(boost::asio::io_service& io_service, bool listen, string Client_ip) : socket_(io_service) 
{
	try{
		//Open send socket
		socket_.open(udp::v4());

		//bind retreive socket
		if(listen)
		{
			//udp::endpoint local_endpoint = udp::endpoint(boost::asio::ip::address::from_string(Local_ip), Client_port);
			udp::endpoint local_endpoint = udp::endpoint(boost::asio::ip::address_v4::any(), Client_port);
			socket_.bind(local_endpoint);
		}
		else
		{
			remote_endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(Client_ip),  Client_port);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void Client_Connection::sendPacket(Client_Packet& packet)
{
	//socket_.async_send_to(packet.getBuffer(), remote_endpoint, 0, ignored_error);
	socket_.send_to(boost::asio::buffer(packet.getBuffer()), remote_endpoint, 0, ignored_error);
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

