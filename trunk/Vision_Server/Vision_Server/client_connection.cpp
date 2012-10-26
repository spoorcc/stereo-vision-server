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

boost::array<uint8_t, Client_Connection::PACKET_MAXSIZE> Client_Connection::read(void)
{
	boost::array<uint8_t, PACKET_MAXSIZE> recv_buf;
	try
	{
		udp::endpoint sender_endpoint;

		printf("Start Receiving...");

		size_t len = socket_.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);

		printf("Received from: %s\n", sender_endpoint.address().to_string());

		return recv_buf;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return recv_buf;
}

