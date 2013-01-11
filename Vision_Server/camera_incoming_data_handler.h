#ifndef CAMERA_INCOMING_DATA_HANDLER_H
#define CAMERA_INCOMING_DATA_HANDLER_H

#include <QObject>
#include <QDebug>
#include <stdio.h>
#include "qpcap/qpcap_qpcapethernetpacket.h"
#include "qpcap/qpcap_qpcapippacket.h"
#include "qpcap/qpcap_qpcapudppacket.h"
#include "qpcap/qpcap_qpcaptcppacket.h"
#include "const.h"

class Camera_Incoming_Data_Handler : public QObject
{
    Q_OBJECT
public:
    explicit Camera_Incoming_Data_Handler(QObject *parent = 0);
public slots:
    void handleData(const uchar*);
private:
    void printRawData(const uchar*);
};

#endif // CAMERA_INCOMING_DATA_HANDLER_H
