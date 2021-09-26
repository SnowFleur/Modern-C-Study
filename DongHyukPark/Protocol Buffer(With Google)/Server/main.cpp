#pragma once

//Only Used x64
#ifdef _DEBUG
    #pragma comment(lib,"Debug\\Basic-SnowNetCore.lib")
    #pragma comment(lib,"Debug\\libprotobufd.lib")
#else
    #pragma comment(lib,"Release\\Basic-SnowNetCore.lib")
    #pragma comment(lib,"Release\\libprotobuf.lib")
#endif // _DEBUG

#include<WindowsHeader.h>
#include<SnowThread.h>
#include<iostream>
#include"Server.h"

int main() {
    CServer server;
    while (true)Sleep(100);
}