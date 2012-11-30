#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <pcap.h>

#include "camera_packet.h"

#define LINE_LEN 16

using namespace std;

class Camera_Connection {
public:
	int chooseEthernetCard(void);
	bool receivePacket(void);
	void sendPacket(Camera_Packet & packet);

private:

	pcap_if_t *alldevs, *d;
	pcap_t *fp;
	u_int inum, i;
	char errbuf[PCAP_ERRBUF_SIZE];
	int res;
	struct pcap_pkthdr *header;
	const u_char *pkt_data;

	

};

