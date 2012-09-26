#include "includes.h"

using namespace std;
using namespace boost; 

void main()
{
	cout <<	"----------------------------------\n";
	cout <<	"--  Starting Vision Server v0.2 --\n";
	cout <<	"----------------------------------\n";

	cout << "[Main Server] Main server started\n";

    thread thread_1 = thread(startCameraManager);
	thread thread_2 = thread(startGraphicsManager);
	thread thread_3 = thread(startClientManager);

	for(;;)
	{
	}
}
