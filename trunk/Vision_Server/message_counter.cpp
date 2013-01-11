#include "message_counter.h"

Message_Counter::Message_Counter(QObject *parent) : QObject(parent)
{
    printf("[Message Counter] Starting counter... \n");

    if(msgTimer->isActive())
    {
        printf("[Message Counter] Active!\n");
    }
    else
    {
        printf("[Message Counter] NOT Active!\n");
    }

}

void Message_Counter::printMessages(void)
{
	messagesClientSentCount = 0;
	messagesClientReceivedCount = 0;
    printf("[Client Manager] Messages sent: %d/sec, received: %d/sec \n", messagesClientSentCount, messagesClientReceivedCount);
}

void Message_Counter::countSendUp(void)
{
	messagesClientSentCount++;
}

void Message_Counter::countReceivedUp(void)
{
	messagesClientReceivedCount++;
}
