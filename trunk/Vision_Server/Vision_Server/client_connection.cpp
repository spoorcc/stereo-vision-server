#include "client_connection.h"

using namespace std;

Client_Connection::Client_Connection(void) {
}

void Client_Connection::connectToClient(char* client_ip, int client_port)
{
	WSAData wsaData;
    WORD DLLVERSION;
    DLLVERSION = MAKEWORD(2,1);
    answer = WSAStartup(MAKEWORD(2,2), &wsaData);

	//sConnect = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //AF_INET: IPv4, SOCK_DGRAM: UDP datagrams,  IPPROTO_UDP: UDP protocol

	addr.sin_addr.s_addr = inet_addr(client_ip);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(client_port);

	cout << "[Client Manager] Listen to clients\n";
	answer = connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
}

void Client_Connection::listenToClients(void)
{
	slisten = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//
	answer = bind(slisten, (SOCKADDR*)&addr, sizeof(addr));
	if (answer == SOCKET_ERROR) {
        wprintf(L"bind function failed with error %d\n", WSAGetLastError());
        answer = closesocket(slisten);
        if (answer == SOCKET_ERROR)
            wprintf(L"closesocket function failed with error %d\n", WSAGetLastError());
        WSACleanup();
        return;
    }
	// unlimited clients
	if (listen(slisten, SOMAXCONN) == SOCKET_ERROR)
        wprintf(L"listen function failed with error: %d\n", WSAGetLastError());

	//conditions
	for(;;)
	{
		cout <<"waiting for client" <<endl;
		char buf[1027];
		if (answer = recv(sConnect, buf, sizeof(buf), NULL))
		{
			if (answer > 0 )
				printf("Bytes received: %d\n", answer);
			else if (answer == 0 )
				printf("Connection closed\n");
			else
				printf("recv failed: %d\n", WSAGetLastError());
			cout<<" A connection was found" <<endl;
		}
	}
}

int Client_Connection::sendPacket(Packet packet){
	//packet.SetHeader();
	return send(sConnect,(char*) packet.getBuffer(), packet.getMsgSize() ,NULL);
}