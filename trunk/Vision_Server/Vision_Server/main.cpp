#include "includes.h"
#include <Windows.h>

using namespace std;
using namespace boost; 

void main()
{
	cout <<	"----------------------------------\n";
	cout <<	"--  Starting Vision Server v0.2 --\n";
	cout <<	"----------------------------------\n";

	cout << "[Main Server] Main server started\n";

   
	//thread thread_2 = thread(startGraphicsManager);
	//Sleep(1000);
	thread thread_3 = thread(startClientManager);
	//Sleep(1000);
	//thread thread_1 = thread(startCameraManager);

	for(;;)
	{
	}
}
