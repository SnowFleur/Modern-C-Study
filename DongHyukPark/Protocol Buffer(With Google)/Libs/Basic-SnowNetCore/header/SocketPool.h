#pragma once

#include<queue>
#include"WindowsHeader.h"
#include"Lock.h"
#include"DataTypes.h"
#include"LogCollector.h"


class CFreeSocketPool
{
private:
    std::queue<SOCKET>  queFreeSocket_;
    CRITICAL_SECTION    cs_;
public:
    CFreeSocketPool(const CFreeSocketPool&)                      = delete;
    CFreeSocketPool(CFreeSocketPool&&)noexcept                   = delete;
    CFreeSocketPool& operator=(const CFreeSocketPool&)           = delete;
    CFreeSocketPool& operator=(CFreeSocketPool&&)noexcept        = delete;

public:
    CFreeSocketPool(size_t socketPoolSize, SOCKET_TYPE socketType) :
        queFreeSocket_()
        , cs_()
    {
        for (size_t i = 0; i < socketPoolSize; ++i)
        {
            SOCKET  temp = INVALID_SOCKET;
            temp = WSASocket(AF_INET, static_cast<int>(socketType), IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
            if (temp != INVALID_SOCKET)
            {
                queFreeSocket_.push(temp);
            }
        }
    }

    ~CFreeSocketPool()
    {

        while (queFreeSocket_.empty() == false)
        {
            SOCKET temp = queFreeSocket_.front();
            if (closesocket(temp) == SOCKET_ERROR)
            {
                PRINT_ERROR_LOG("Socket is SOCKET_ERROR FOr ~CSocketPool()\n");
            }
            queFreeSocket_.pop();
        }
    }

    inline SOCKET PopFreeList()
    {
        STLockGuard lockguard(cs_);
        SOCKET temp = queFreeSocket_.front();
        queFreeSocket_.pop();
        return temp;
    }

    inline void PushFreeList(SOCKET socket)
    {
        STLockGuard lockguard(cs_);
        queFreeSocket_.push(socket);
    }

};
