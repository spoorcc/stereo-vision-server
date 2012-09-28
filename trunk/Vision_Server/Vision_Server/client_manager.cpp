#include "includes.h"
#include "client_manager.h"

using namespace std;

#define CAMERA_IP "127.0.0.1"	//ip address of udp server
#define CAMERA_PORT 51912			//The port on which to listen for incoming data

void startClientManager(void)
{
	//TODO
	cout << "[Client Manager] Client Manager started\n";
	connection = Client_Connection();
	connection.connectToClient(CAMERA_IP,CAMERA_PORT);
	connection.listenToClients();
	for(;;)
	{
	}
}