#include "includes.h"

using namespace std;

class Packet {
	string msg;
  public:
    void create_packet (string);
} Packet;

void Packet::create_packet (string header) {
  msg = "test";
}