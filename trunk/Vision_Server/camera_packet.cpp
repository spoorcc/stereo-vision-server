#include "camera_packet.h"

Camera_Packet::Camera_Packet(QObject *parent)
{
    // set mac destination address to 00 : 00 : 00 : 00 : 05 : 00
    buffer[0] = 0x00;
    buffer[1] = 0x00;
    buffer[2] = 0x00;
    buffer[3] = 0x00;
    buffer[4] = 0x05;
    buffer[5] = 0x00;

    // set mac source address to 14 : fe : b5 : be : 6d : 02
    buffer[6]  = 0x14;
    buffer[7]  = 0xfe;
    buffer[8]  = 0xb5;
    buffer[9]  = 0xbe;
    buffer[10] = 0x6d;
    buffer[11] = 0x09;

    // Ether Type
    buffer[12] = 0x08;
    buffer[13] = 0x00;

    // Version, header lenght, Differentiated Services, Total Length.
    buffer[14] = 0x45;
    buffer[15] = 0x00;
    buffer[16] = 0x01;
    buffer[17] = 0x20;

    // Identification, Flags , Fragment Offset
    buffer[18] = 0x05;
    buffer[19] = 0x42;
    buffer[20] = 0x00;
    buffer[21] = 0x00;

    // Time to Live
    buffer[22] = 0x01;
    // Protocol
    buffer[23] = 0x11;
    // Header Chechksum
    buffer[24] = 0x70;
    buffer[25] = 0x20;

    // Source Address
    buffer[26] = 0xA9;
    buffer[27] = 0xFE;
    buffer[28] = 0xB8;
    buffer[29] = 0x70;

    // Destination Adress
    buffer[30] = 0xE0;
    buffer[31] = 0x00;
    buffer[32] = 0x00;
    buffer[33] = 0xFC;

    // UDP
    // Source Port
    buffer[34] = 0xc3;
    buffer[35] = 0xb5;

    // Destination Port
    buffer[36] = 0x30;
    buffer[37] = 0x37;

    // Length
    buffer[38] = 0x01;
    buffer[39] = 0x0c;

    // Checksum
    buffer[40] = 0x00;
    buffer[41] = 0x00;
}

QByteArray* Camera_Packet::getBuffer()
{
    return &buffer;
}

int Camera_Packet::getBufferSize()
{
    return PACKET_MAXSIZE;
}

void Camera_Packet::appendString(QString c)
{
    buffer.append(c);
}
