#ifndef CLIENT_PACKET_H_
#define CLIENT_PACKET_H_

#include <QObject>
#include <QByteArray>
#include <stdint.h>
#include <iostream>
#include <vector>

class Client_Packet : public QObject
{
    Q_OBJECT
public:
    static const int PACKET_MAXSIZE = 500;
    explicit Client_Packet(QObject *parent, int packet_size);
    bool canAdd(int size);
    uint16_t getMsgSize(void);
    uint8_t readUint8(uint16_t pos);
    uint16_t readUint16(uint16_t pos);
    bool addUint8(uint8_t);
    bool addUint8(uint8_t value, uint16_t pos);
    bool addUint16(uint16_t);
    bool addUint16(uint16_t, uint16_t startPos);
	QByteArray* getBuffer(void);
private:
	QByteArray Buffer;
};

#endif
