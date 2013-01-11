#ifndef CAMERA_CONNECTION_H
#define CAMERA_CONNECTION_H

#include <QObject>
#include <QDebug>
#include <qpcap/qpcap_qpcap.h>

#include "camera_packet.h"

#define MAX_SNAP_LENGTH 65535

class Camera_Connection : public QObject
{
    Q_OBJECT
public:
    explicit Camera_Connection(QObject *parent = 0);
    void sendPacket(Camera_Packet* packet);
signals:
    void newPacket(const uchar *);
private:
    QPcap pcap;
};

#endif /* CAMERA_CONNECTION_H */
