#pragma comment(lib, "Ws2_32.lib")

#include <sdkddkver.h>
#include <conio.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <boost/thread.hpp>
#include<WinSock2.h>
#include<Windows.h>
#include<iostream>

#include "highgui.h"
#include <cv.h>

void connectServer();
void camera(void);