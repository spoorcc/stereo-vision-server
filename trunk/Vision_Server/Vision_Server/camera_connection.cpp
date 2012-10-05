#include "camera_connection.h"
//#include <boost/array.hpp>
//#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::udp;

#define Cam_ip "127.0.0.1"
#define Cam_port 51912

#define Local_ip "127.0.0.1"

Camera_Connection::Camera_Connection(boost::asio::io_service& io_service, bool listen) : socket_(io_service) {
	try{
		//Open send socket
		socket_.open(udp::v4());
		//boost::asio::socket_base::broadcast option(true);
		//socket_.set_option(option);

		remote_endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(Cam_ip),  Cam_port);

		//open retreive socket
		if(listen){
			udp::endpoint local_endpoint = udp::endpoint(boost::asio::ip::address::from_string(Local_ip), Cam_port);
			socket_.bind(local_endpoint);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void Camera_Connection::sendPacket(Packet& packet)
{
	//Verzenden
	//std::cout << "Send to " << remote_endpoint << std::endl;
	socket_.send_to(boost::asio::buffer(packet.getBuffer(), 260), remote_endpoint, 0, ignored_error);
}

boost::array<uint8_t, 260> Camera_Connection::read(void)
{
	boost::array<uint8_t, 260> recv_buf;
	try
	{
		udp::endpoint sender_endpoint;
		size_t len = socket_.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);
		//socket_.receive(boost::asio::buffer(recv_buf));
		return recv_buf;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return recv_buf;
}