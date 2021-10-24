#pragma once
/*
- Developer: SnowFleur
- Descriptor: 윈도우헤더 모음
*/

#define _WINSOCKAPI_

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <mswsock.h>            //AcceptEX
#include <process.h>           //BeginThreadEx, EndThreadEx
#include<ws2tcpip.h>            //Inet_ntop
#include<mstcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "mswsock.lib")
#endif