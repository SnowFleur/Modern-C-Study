#pragma once

#include<queue>
#include<atomic>

#include"WindowsHeader.h"
#include"DataTypes.h"
#include"SnowSocket.h"
#include"Buffer.h"
#include"NetAddress.h"

/*
-   [2021.09.10]
-   Network기능을 상속받는 Session
-	네트워크 기능들을 사용할 수 있음
-
*/

class CSnowSession : public CSnowSocket
{
    //To do std::any
    typedef void* Packet;
private:
    CNetAddress                         sessionAddress_;
    SessionID                           sessionId_;
    CBuffer<char>                       sendBuffer_;
    CBuffer<char>                       recvBuffer_;
    bool                                isAlive_;
    std::atomic<bool>                   sendComplete_;
    std::queue<Packet>                  sendQueue_;
public:
    CSnowSession& operator=(const CSnowSession&)     = delete;
    CSnowSession(const CSnowSession&)                = delete;
    CSnowSession& operator=(CSnowSession&&)noexcept  = delete;
    CSnowSession(CSnowSession&&)noexcept             = delete;

    CSnowSession(const SOCKET_TYPE socketType, const SessionID sessionID);

    virtual ~CSnowSession()noexcept;
public:
    
    inline SessionID GetSessionID()const                          { return sessionId_; }
    inline void SeSessionID(const SessionID sessionId)            { sessionId_ = sessionId; }
    inline void SetAlive(const bool alive)                        { isAlive_ = alive; }
    inline bool GetAlive()const                                   { return isAlive_; }
    PSOCKADDR_IN GetSessionAddr()                                 { return sessionAddress_.GetAddrInfor(); }
    void SetSessionAdder(PSOCKADDR pRemoteSocketAddr)             { sessionAddress_.SetAddrInfor(pRemoteSocketAddr); };
    void PrintSessionAddrInfor()const                             { sessionAddress_.PrintIPAndPort(); }

    auto GetRecvBuffer()                                          { return recvBuffer_.GetBuffer(); }
    auto SetRecvBuffer(const char* buffer, uint32_t bufferSize)   { recvBuffer_.SetBuffer(buffer, bufferSize); }
    auto GetRecvBufferSize()const                                 { return recvBuffer_.GetBufferSize(); }
    
    auto GetSendBuffer()                                          { return sendBuffer_.GetBuffer(); }
    auto SetSendBuffer(const char* buffer, uint32_t bufferSize)   { sendBuffer_.SetBuffer(buffer, bufferSize); }
    auto GetSendBufferSize()const                                 { return sendBuffer_.GetBufferSize(); }

    DWORD           OnRecv();
    DWORD           OnSend();
    void            PushSendQueue(Packet packet);
};

























