#pragma once
/*
- Developer: PDH
- Descriptor: Server 역할을 수행하는 Class
- ProtoBuf 확인용 심플 서버임
*/

#include<atomic>
#include<LogCollector.h>
#include<SnowServer.h>
#include"../protocol/TestProtoBufProtocol.pb.h"
#include"PacketHandler.h"


class CIocpServer : public CSnowServer
{
private:
    std::vector<CSnowSession*>       vecSnowSession_;
    volatile LONG                    sessoinCount_;

public:
    CIocpServer(uint32_t workerThreadCount, bool isStartThread, const char* pServerIP, const USHORT port) :
        CSnowServer(pServerIP, port)
    {
        CreateWorkerTherad(workerThreadCount, isStartThread);
        vecSnowSession_.reserve(1000);
    }

    void StartIocpServer()
    {
        PRINT_INFO_LOG("Start Sever\n");
        CSnowServer::StartSnowServer();
    }

    //overrride Funcions
public:
    void CompletedAccpet(CSnowSession* pAcceptCompleteSession) override
    {
        if (pAcceptCompleteSession == nullptr)
        {
            PRINT_ERROR_LOG("pAcceptCompleteSession is nullptr\n");
            return;
        }

		PRINT_INFO_LOG(__FUNCTION__, "\n");

        InterlockedAdd(&sessoinCount_, sessoinCount_ + 1);

		pAcceptCompleteSession->SetSessionID(sessoinCount_);
		vecSnowSession_.push_back(pAcceptCompleteSession);
		pAcceptCompleteSession->OnRecv();

    }
    virtual void CompletedSend(CSnowSession* pSendCompleteSession, const DWORD sendByte)override
    {
        PRINT_INFO_LOG(__FUNCTION__, " SessionID:", pSendCompleteSession->GetSessionID(), " Send Byte: ", sendByte, "\n");
        pSendCompleteSession->OnRecv();
    }
    virtual void CompletedRecv(CSnowSession* pRecvCompleteSession, const DWORD recvByte)override
    {
        PRINT_INFO_LOG(__FUNCTION__, " SessionID:", pRecvCompleteSession->GetSessionID(), " Recv Byte: ", recvByte, "\n");
        TestProtoBufProtocol::CS_LOGIN_REQ  csLoginPacket;
        if (DegeneratedProtoBuf(&csLoginPacket, pRecvCompleteSession->GetRecvBuffer(), pRecvCompleteSession->GetRecvBufferSize()) == true)
        {
            TestProtoBufProtocol::SC_LOING_RES scLoginPacket;

            scLoginPacket.set_sessionindex(pRecvCompleteSession->GetSessionID());
            if (GeneratedProtoBuf(&scLoginPacket, pRecvCompleteSession->GetSendBuffer(), pRecvCompleteSession->GetSendBufferSize(), PT::SC_LOING_RES) == true)
            {
                if (pRecvCompleteSession->OnSend() > 0) 
                {
                    PRINT_INFO_LOG("Send\n");
                }

            }
        }
    }


};
