#include <sdkddkver.h>
#include <conio.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <boost/thread.hpp>

using namespace std;
using namespace boost; 

void startCameraManager(void);
void startGraphicsManager(void);
void startClientManager(void);

void main()
{
	cout <<	"----------------------------------\n";
	cout <<	"--  Starting Vision Server v0.3 --\n";
	cout <<	"----------------------------------\n";

	cout << "[Main Server] Main server started\n";
   
	//thread thread_2 = thread(startGraphicsManager);
	thread thread_3 = thread(startClientManager);
	thread thread_1 = thread(startCameraManager);

	for(;;)
	{
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000)); 
	}
}
