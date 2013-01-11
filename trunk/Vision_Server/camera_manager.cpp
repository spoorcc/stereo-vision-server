#include "camera_manager.h"

Camera_Manager::Camera_Manager(QObject *parent) : QObject(parent)
{
    printf("[Camera Manager] Camera Manager started.\n");

    this->connect( &connection, SIGNAL(newPacket(const uchar *)), &dataHandler, SLOT(handleData(const uchar *)) );
}
