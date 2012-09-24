#include "includes.h"

using namespace std;

void main()
{

	using namespace boost; 
    thread thread_1 = thread(connectServer);
//	thread thread_2 = thread(camera);

	for(;;)
	{
	}
}

void connectServer()
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
/*
void camera(void)
{
	CvCapture* capture;
	IplImage* img = 0;


        capture = cvCreateCameraCapture(0);
        img = cvQueryFrame(capture);
        cvNamedWindow( "Example1", CV_WINDOW_AUTOSIZE );
        cvShowImage("Example1", img);
        cvWaitKey(50);
        cvReleaseImage( &img );
        cvDestroyWindow("Example1");
}
*/