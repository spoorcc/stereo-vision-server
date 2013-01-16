#include "camera_manager.h"

Camera_Manager::Camera_Manager(Graphics_Manager* graphMan, QObject *parent) : QObject(parent)
{
    printf("[Camera Manager] Camera Manager started.\n");

    this->connect( &connection, SIGNAL(newPacket(const uchar *)), &dataHandler, SLOT(handleData(const uchar *)) );

    int i = 0;
    Camera_Packet testPacket;
    testPacket.reset();

    QByteArray* test = graphMan->getBuffer(0);

    qDebug() << "[Camera Manager] " << test->size();

    for(i = 0; i < 300; i++)
    {
        testPacket.changeAllHeaders(0xB0, i * 128,false);
        testPacket.addBuffer(prepareSendArray(test,i));
        connection.sendPacket(&testPacket);
    }
}

QByteArray Camera_Manager::prepareSendArray(QByteArray* fromQbyteArray, int nr)
{
    QByteArray sendQbyteArray;

    for(int i = 0; i < 1024;i++)
    {
        sendQbyteArray[i] = fromQbyteArray->at(nr * 1024 + i);
    }
    return sendQbyteArray;
}




