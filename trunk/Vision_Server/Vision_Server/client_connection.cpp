#include "client_connection.h"


#define Client_ip  "145.48.115.192" //"192.168.123.4" 
#define Client_port 49679

using namespace std;



Client_Connection::Client_Connection(boost::asio::io_service& io_service, bool listen) : socket_(io_service) 
{
	try{
		//Open send socket
		socket_.open(udp::v4());

		remote_endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(Client_ip),  Client_port);

		//bind retreive socket
		if(listen){
			//udp::endpoint local_endpoint = udp::endpoint(boost::asio::ip::address::from_string(Local_ip), Client_port);
			udp::endpoint local_endpoint = udp::endpoint(boost::asio::ip::address_v4::any(), Client_port);
			socket_.bind(local_endpoint);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void Client_Connection::sendPacket(Client_Packet& packet)
{
	socket_.send_to(boost::asio::buffer(packet.getBuffer(), packet.getMsgSize()), remote_endpoint, 0, ignored_error);
}

string Client_Connection::read(boost::array<uint8_t, Client_Connection::PACKET_MAXSIZE>& msg)
{
	try
	{
		udp::endpoint sender_endpoint;

		printf("Start Receiving...\n");

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

