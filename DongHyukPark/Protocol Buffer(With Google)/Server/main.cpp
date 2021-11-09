#pragma once
/*
- Developer: PDH
- Descriptor: main
- �����ϰ� ���� lib �۵� Ȯ�� �� Protobuf ���ο� Project
*/

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

#define SERVER_ADDDR "127.0.0.1"
constexpr int PORT = 9000;


int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    CIocpServer server(4);
    server.StartIocpServer(SERVER_ADDDR, PORT);
}

