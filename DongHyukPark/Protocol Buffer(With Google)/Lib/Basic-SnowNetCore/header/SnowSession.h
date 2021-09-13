#pragma once

#include"WindowsHeader.h"
#include"DataTypes.h"
#include"SnowSocket.h"
#include"Buffer.h"
#include<queue>

/*
-   [2021.09.10]
-   Network기능을 상속받는 Session
-	네트워크 기능들을 사용할 수 있음
-
*/

class CSnowSession: public CSnowSocket{
    //To do Std::any
    typedef void* Packet;
private:
    //CNetAddress           sessionAddress_;
    SessionID				sessionId_;
    CBuffer					sendBuffer_;
    CBuffer					recvBuffer_;
    std::atomic<bool>       sendComplete_;
    std::queue<Packet>      sendQueue_;
private:
	bool PacketValidCheck(const char* packet);
public:
	CSnowSession& operator=(const CSnowSession&)    = delete;
	CSnowSession& operator=(CSnowSession&&)         = delete;
	CSnowSession(const CSnowSession&)               = delete;
	CSnowSession(CSnowSession&&)                    = delete;

    CSnowSession(const SOCKET_TYPE socketType, const SessionID sessionID, const uint32_t BUFFER_SIZE);
	virtual ~CSnowSession()noexcept;
public:
    inline SessionID        GetSessionID()const { return sessionId_; }
    inline void				SetSessionID(const SessionID sessionId) { sessionId_ = sessionId; }
    inline const char*      GetRecvBuffer()const { return  recvBuffer_.GetBuffer(); }
    bool                    OnRecv();
    bool                    OnSend(Packet packet);
    void                    PushSendQueue(Packet packet);

};

























