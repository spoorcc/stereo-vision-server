#include "camera_connection.h"

using namespace std;

// Create new packet with 1 byte header
Camera_Connection::Camera_Connection(void) {
}

void Camera_Connection::connectToCamera(char* cam_ip, int cam_port)
{
	sconnect = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //AF_INET: IPv4, SOCK_DGRAM: UDP datagrams,  IPPROTO_UDP: UDP protocol
	addr.sin_addr.s_addr = inet_addr(cam_ip);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(cam_port);

	cout << "[Camera Manager] Establishing UDP connection to camera\n";
	connect(sconnect, (SOCKADDR*)&addr, sizeof(addr));
}

int Camera_Connection::sendPacket(Packet packet){
	//packet.SetHeader();
	return send(sconnect,(char*) packet.getBuffer(), packet.getMsgSize() ,NULL);
}