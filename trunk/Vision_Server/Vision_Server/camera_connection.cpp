#include "camera_connection.h"
//#include <boost/array.hpp>
//#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::udp;

Camera_Connection::Camera_Connection(boost::asio::io_service& io_service) : socket_(io_service) {
	try{
		//Open send socket
		socket_.open(udp::v4());

		boost::asio::socket_base::broadcast option(true);
		socket_.set_option(option);

		remote_endpoint = boost::asio::ip::udp::endpoint(
		boost::asio::ip::address::from_string("127.0.0.1"),  51912);

		//open retreive socket
		udp::endpoint local_endpoint = udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 51912);
		socket_.bind(local_endpoint);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void Camera_Connection::sendPacket(Packet packet)
{
	//Verzenden
	//std::cout << "Send to " << remote_endpoint << std::endl;
	socket_.send_to(boost::asio::buffer(packet.getBuffer(), 1028), remote_endpoint, 0, ignored_error);
}

boost::array<uint8_t, 1028> Camera_Connection::read(void)
{
	boost::array<uint8_t, 1028> recv_buf;
	try
	{
		socket_.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);
		return recv_buf;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return recv_buf;
}