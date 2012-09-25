#include "includes.h"

using namespace std;

void main()
{
	using namespace boost; 

    thread thread_1 = thread(startCameraManager);
	thread thread_2 = thread(startGraphicsManager);
	thread thread_3 = thread(startClientManager);

	for(;;)
	{
	}
}
