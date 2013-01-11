#ifndef MESSAGE_COUNTER_H_
#define MESSAGE_COUNTER_H_

#include <QDebug>
#include <QObject>
#include <QTimer>
#include <stdint.h>
#include <stdio.h>

class Message_Counter : public QObject
{
    Q_OBJECT
public:
    explicit Message_Counter(QObject *parent = 0);
public slots:
    void countReceivedUp(void);
    void countSendUp(void);
    void printMessages(void);
private:
	uint32_t messagesClientReceivedCount;
	uint32_t messagesClientSentCount;
    QTimer* msgTimer;
};
#endif /*MESSAGE_COUNTER_H_*/
