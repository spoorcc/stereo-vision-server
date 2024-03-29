#ifndef CAMERA_PACKET_H
#define CAMERA_PACKET_H

#include <QObject>
#include <QByteArray>

#include <string>
#include <stdint.h>
#include <iostream>

class Camera_Packet : public QObject
{
    Q_OBJECT
public:
    static const int PACKET_MAXSIZE = 1500;
    explicit Camera_Packet(QObject *parent = 0);
    QByteArray* getBuffer();
    int getBufferSize();
    void appendString(QString c);
    void reset();
    void changeAllHeaders(uint8_t _header, uint16_t _range, bool _read);
    void addBuffer(QByteArray buf);
private:
    QByteArray buffer;

};
#endif
