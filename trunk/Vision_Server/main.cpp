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
    //Camera Manager
    //Camera_Manager camMan(&app);
    //////////////////////////////

    //camMan.moveToThread(&camManThread);
    //camManThread.start();

    //////// Graphics Manager
    //QThread graphManThread;
    //Graphics_Manager graphMan;
    //graphMan.moveToThread(&graphManThread);
    //graphManThread.start();

	//////// Client Manager
    //QThread clManThread;
    Client_Manager clMan(&app);
    //clMan.moveToThread(&clManThread);
    //clManThread.start();



    return app.exec();
}
