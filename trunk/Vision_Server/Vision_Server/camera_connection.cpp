#include "camera_connection.h"

using namespace std;

int Camera_Connection::chooseEthernetCard(void){

	i = 0;
        /* The user didn't provide a packet source: Retrieve the local device list */
        if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)
        {
            fprintf(stderr,"Error in pcap_findalldevs_ex: %s\n", errbuf);
            return -1;
        }
        
        /* Print the list */
        for(d=alldevs; d; d=d->next)
        {
            printf("%d. %s\n    ", ++i, d->name);

            if (d->description)
                printf(" (%s)\n", d->description);
            else
                printf(" (No description available)\n");
        }
        
        if (i==0)
        {
            fprintf(stderr,"No interfaces found! Exiting.\n");
            return -1;
        }
        
        printf("Enter the interface number (1-%d):",i);
        scanf_s("%d", &inum);
        
       if (inum < 1 || inum > i)
        {
            printf("\nInterface number out of range.\n");

            /* Free the device list */
            pcap_freealldevs(alldevs);
            return -1;
        }
        
        /* Jump to the selected adapter */
        for (d=alldevs, i = 0; i < inum-1 ;d=d->next, i++);
        
        /* Open the device */
        if ( (fp= pcap_open(d->name,
                            100 /*snaplen*/,
                            PCAP_OPENFLAG_PROMISCUOUS /*flags*/,
                            20 /*read timeout*/,
                            NULL /* remote authentication */,
                            errbuf)
                            ) == NULL)
        {
            fprintf(stderr,"\nError opening adapter\n");
            return -1;
        }

		fprintf(stderr,"\verbinding is klaar\n");
}

void Camera_Connection::sendPacket(Camera_Packet & packet){
		pcap_sendpacket
							(	fp, // the adapter handle
							packet.getBuffer(), // the packet
							packet.getMsgSize() // the length of the packet
							);
}


bool Camera_Connection::receivePacket(void){

//	while((res = pcap_next_ex( fp, &header, &pkt_data)) >= 0){

	if((res = pcap_next_ex( fp, &header, &pkt_data)) >= 0){
		
		if(res == 0){
			return false;
		}
		else{
			/*printf("Destination MAC\n");
			for(int i = 0; i < 6; i++){
				printf("%.2x ", pkt_data[i]);
			}*/
			return true;
		}
	}
	/*	printf("\n");
		printf("Source MAC\n");
		for(int i = 6; i < 12; i++){
			printf("%.2x ", pkt_data[i]);
		}
		printf("\n");
		printf("Source Adress\n");
		for(int i = 26; i < 30; i++){
			printf("%d ", pkt_data[i]);
		}
		printf("\n");
		printf("Destination Adress\n");
		for(int i = 30; i < 34; i++){
			printf("%d ", pkt_data[i]);
		}
		printf("\n\n");
        /* Print the packet */
      /*  for (i=1; (i < header->caplen + 1 ) ; i++){
            printf("%.2x ", pkt_data[i-1]);
            if ( (i % LINE_LEN) == 0) printf("\n");
        }*/
//	}
}

