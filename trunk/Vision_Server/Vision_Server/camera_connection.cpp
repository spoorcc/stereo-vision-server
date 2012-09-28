#include "camera_connection.h"
#include <boost/array.hpp>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::udp;


Camera_Connection::Camera_Connection(void) {
}

void Camera_Connection::connectToCamera(char* cam_ip, int cam_port)
{
	WSAData wsaData;
    WORD DLLVersion;
	DLLVersion = MAKEWORD(2,2);
    answer = WSAStartup(DLLVersion, &wsaData);
    if (answer != NO_ERROR) {
      printf("WSAStartup failed: %d\n", answer);
	  return;
    }

	sconnect = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //AF_INET: IPv4, SOCK_DGRAM: UDP datagrams,  IPPROTO_UDP: UDP protocol
	addr.sin_addr.s_addr = inet_addr(cam_ip);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(cam_port);

	cout << "[Camera Manager] Establishing UDP connection to camera\n";
	connect(sconnect, (SOCKADDR*)&addr, sizeof(addr));

}

long Camera_Connection::sendPacket(Packet packet)
{

	//printf((char *) packet.getBuffer());
	//packet.SetHeader();
	//answer = send(sconnect,(char*) packet.getBuffer(), 7 ,NULL);
	answer = send(sconnect,"bericht", 7 ,NULL);
	return answer;
}

char* Camera_Connection::read()
{
  try
  {

    boost::asio::io_service io_service;

    udp::endpoint local_endpoint = boost::asio::ip::udp::endpoint(
	  boost::asio::ip::address::from_string("127.0.0.1"), 51912);
    std::cout << "Local bind " << local_endpoint << std::endl;
 
// MODE 1: WORKS  
//    udp::socket socket(io_service, local_endpoint);

// MODE 2: WORKS
//    udp::socket socket(io_service, udp::endpoint(udp::v4(), boost::lexical_cast<int>(argv[2]) )),

// MODE 3: WORKS
    udp::socket socket(io_service);
    socket.open(udp::v4());
    socket.bind(local_endpoint);
///////////////
	boost::array<char, 1027> recv_buf;
	udp::endpoint sender_endpoint;
	for(;;){

		size_t len = socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);

		std::cout.write(recv_buf.data(), len);
	}
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }


  return "test";
}