#include "camera_connection.h"

Camera_Connection::Camera_Connection(QObject *parent) : QObject(parent)
{    
    QString device = pcap.lookupDevice();
    if ( device.isEmpty() ) {
        qDebug() << "Lookup device failed, " << pcap.errorString();
        //return 1;
    }

    bool ok;
    ok = pcap.open( device, MAX_SNAP_LENGTH, true );
    if (!ok) {
        qDebug() << "Unable to open, " << pcap.errorString();
        //return 1;
    }

    this->connect(&pcap, SIGNAL(packetReady(const uchar*)), this, SIGNAL(newPacket(const uchar*)));

    qDebug() << "[Camera Connection] Packet Capture started on " << device;

    pcap.start();
}

void Camera_Connection::sendPacket(Camera_Packet* packet)
{
    pcap.sendPacket(packet->getBuffer());
}
