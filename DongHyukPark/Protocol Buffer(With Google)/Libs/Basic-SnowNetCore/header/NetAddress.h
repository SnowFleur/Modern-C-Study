#pragma once
#include"WindowsHeader.h"
/*
-   [2021.06.26]
-   Network������ ������ class
-
-
*/

class CNetAddress {
private:
    SOCKADDR_IN    acceptClientInfor_;
public:
    CNetAddress();
    
    void                Init();
    void                SetAddrInfor(const PSOCKADDR addrinfor);
    void                PrintIPAndPort()const;
    const PSOCKADDR_IN  GetAddrInfor();
};