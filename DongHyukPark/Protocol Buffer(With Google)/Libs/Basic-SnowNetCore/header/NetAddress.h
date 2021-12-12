#pragma once
/*
- Developer: PDH
- Descriptor: Network정보를 가지는 class
*/

#include"WindowsHeader.h"

class CNetAddress
{
private:
    SOCKADDR_IN    sockAddrInfo_;
public:
    CNetAddress();
    
    void                Init();
    void                SetAddrInfor(const PSOCKADDR addrinfor);
    void                SetAddrInfor(const char* ip, const USHORT port);
    void                PrintIPAndPort()const;
    const PSOCKADDR_IN  GetAddrInfor();
};