#include "message_counter.h"

Message_Counter::Message_Counter(QObject *parent) : QObject(parent)
{
    printf("[Message Counter] Starting counter... \n");

    msgTimer = new QTimer(0);
    msgTimer->start(1000);

    if(msgTimer->isActive())
    {
        qDebug() << "[Message Counter] Active!";
    }
    else
    {
        qDebug() << "[Message Counter] NOT Active!";
    }

    this->connect(msgTimer, SIGNAL( timeout(void) ), SLOT( printMessages() ));
}

void Message_Counter::printMessages(void)
{
	messagesClientSentCount = 0;
	messagesClientReceivedCount = 0;
    if(messagesClientSentCount != 0 || messagesClientReceivedCount != 0)
    {
        printf("[Client Manager] Messages sent: %d/sec, received: %d/sec \n", messagesClientSentCount, messagesClientReceivedCount);
    }
}

void Message_Counter::countSendUp(void)
{
	messagesClientSentCount++;
}

void Message_Counter::countReceivedUp(void)
{
	messagesClientReceivedCount++;
}
