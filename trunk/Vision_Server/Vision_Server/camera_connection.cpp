#include "camera_connection.h"
//#include <boost/array.hpp>
//#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::udp;


Camera_Connection::Camera_Connection(void) {
}

void Camera_Connection::sendPacket(Packet packet)
{
	boost::asio::io_service io_service;
	boost::asio::ip::udp::socket socket(io_service);
	boost::asio::ip::udp::endpoint remote_endpoint;
	bool broadcast = true;

	socket.open(boost::asio::ip::udp::v4());

	// TO ENABLE BROADCAST
	if(broadcast)
	{
		boost::asio::socket_base::broadcast option(true);
		socket.set_option(option);
	}
   
	remote_endpoint = boost::asio::ip::udp::endpoint(
    boost::asio::ip::address::from_string("127.0.0.1"),  51912);
    
	boost::system::error_code ignored_error;

	std::cout << "Send to " << remote_endpoint << std::endl;

	//Verzenden

	socket.send_to(boost::asio::buffer(packet.getBuffer(), 1028), remote_endpoint, 0, ignored_error);
}

void setReadConnection(void)
{
	try
	{
		udp::endpoint local_endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("192.168.1.116"), 51912);
	//	std::cout << "Local bind " << local_endpoint << std::endl;
 
		boost::asio::io_service read_io_service;
		udp::socket socket(read_io_service);
		socket.open(udp::v4());
		socket.bind(local_endpoint);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

}

boost::array<uint8_t, 1028> Camera_Connection::read(void)
{
	boost::array<uint8_t, 1028> recv_buf;
	try
	{
		udp::endpoint sender_endpoint;
		udp::endpoint local_endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 51912);
//		std::cout << "Local bind " << local_endpoint << std::endl;
 
		boost::asio::io_service read_io_service;
		udp::socket socket(read_io_service);
		socket.open(udp::v4());
		socket.bind(local_endpoint);

		size_t len = socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);

		return recv_buf;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
//	return recv_buf;
}