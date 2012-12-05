#include "client_manager.h"
#include "graphics_manager.h"
#include "camera_manager.h"

using namespace std;
using namespace boost; 

void main()
{
	cout <<	"----------------------------------\n";
	cout <<	"--  Starting Vision Server v0.3 --\n";
	cout <<	"----------------------------------\n";

	cout << "[Main Server] Main server started\n";
	
	Graphics_Manager grMan = Graphics_Manager();
	Client_Manager clMan = Client_Manager();
	Camera_Manager camMan = Camera_Manager();

	for(;;)
	{
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000)); 
	}
}
