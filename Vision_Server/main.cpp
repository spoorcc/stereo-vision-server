#include <QCoreApplication>

#include "client_manager.h"
//#include "graphics_manager.h"
#include "camera_manager.h"
#include <QThread>
#include <QDebug>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    printf("----------------------------------\n");
    printf("--  Starting Vision Server v0.3 --\n");
    printf("----------------------------------\n");

    printf("[Main Server] Main server started\n");

    //////// Camera Manager
    //QThread camManThread;

    //////////////////////////////

    //////// Graphics Manager
    Graphics_Manager graphMan(&app);

    //Camera Manager
    //Camera_Manager camMan(&graphMan, &app);

	//////// Client Manager
    Client_Manager clMan(&graphMan, &app);

    return app.exec();
}
