#pragma comment(lib, "Ws2_32.lib")

#include <string>
#include <iostream>


class Packet {
public:
	Packet();
	void addToPacket (int); //TODO String!! geeft errors
private:
	int msg;
};