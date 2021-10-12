#pragma once

#include<iostream>
#include<queue>
#include"WindowsHeader.h"
#include"Lock.h"

class CSocketPool
{
private:
    std::queue<SOCKET>  m_freeSocketList;
    size_t              m_poolSize;
    Lock                m_freeListLock;    

    CSocketPool(const CSocketPool&);
    CSocketPool& operator=(const CSocketPool&);
public:
    CSocketPool(size_t SocketPooSize):
    m_poolSize(SocketPooSize),
    m_freeSocketList()
    {

        for(size_t i=0; i<m_poolSize;++i){
            SOCKET temp=INVALID_SOCKET;
            temp=WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);   
            m_freeSocketList.push(temp);  
        }
    }
    ~CSocketPool()
    {

      while (m_freeSocketList.empty() == false) {
        SOCKET temp = m_freeSocketList.front();

        if (closesocket(temp) == SOCKET_ERROR) {
          std::cout << "Error: SocketPool Close socket \n";
        }
        m_freeSocketList.pop();
      }
    }

    inline SOCKET PopFreeList()
    { 
        
        LockGuard lockguard(m_freeListLock);

        SOCKET temp = m_freeSocketList.front();
        
        if(temp!=INVALID_SOCKET){
            m_freeSocketList.pop();
            return temp;
        }
    }

    inline void PushFreeList(SOCKET socket)
    {

        LockGuard lockguard(m_freeListLock);
        
        m_freeSocketList.push(socket);
        
    }

};

#include"ObjectPool.h"
#include"SnowSession.h"

