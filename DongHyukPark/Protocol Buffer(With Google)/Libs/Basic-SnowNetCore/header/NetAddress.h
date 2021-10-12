#pragma once

/*
-   [2021.06.26]
-   Network정보를 가지는 class
-
-
*/

#include"WindowsHeader.h"

class CNetAddress
{
private:
    SOCKADDR_IN    stSockAddrInfor_;
public:
    CNetAddress();
    
    void                Init();
    void                SetAddrInfor(const PSOCKADDR addrinfor);
    void                SetAddrInfor(const char* ip, const USHORT port);
    void                PrintIPAndPort()const;
    const PSOCKADDR_IN  GetAddrInfor();
};