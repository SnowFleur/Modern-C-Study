#pragma once

#ifdef _WIN32
#include <winsock2.h>
#include <process.h> 
#include <windows.h>
#include <mswsock.h>
#include<ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "mswsock.lib")
#endif

