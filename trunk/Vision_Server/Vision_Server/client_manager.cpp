#include "includes.h"

using namespace std;

void startClientManager(void)
{
	long answer;
	WSAData wsaData;
	WORD DLLVERSION;
	DLLVERSION = MAKEWORD(2,1);
	answer = WSAStartup(DLLVERSION, &wsaData);

	SOCKADDR_IN addr;

	int addrlen = sizeof(addr);

	SOCKET sConnect;

	sConnect = socket(AF_INET, SOCK_STREAM,NULL);

	///////////////////////////////////////////////////////
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12343);

	string confirm;
	char message[200];
	string strMessage;

	cout << "do you want to connect whit the server?? [y/n]" << endl;
	cin >> confirm;

	if(confirm == "y")
	{
		connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
		cout<< "verbind is gemaakt"<<endl;

		while (true)
		{
		answer = recv(sConnect, message, sizeof(message), NULL);
		strMessage = message;
		cout << message << endl;
		}
	}
}