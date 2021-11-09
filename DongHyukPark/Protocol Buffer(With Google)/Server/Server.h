#pragma once
/*
- Developer: PDH
- Descriptor: Server 역할을 수행하는 Class
- ProtoBuf 확인용 심플 서버임
*/

#include<atomic>
#include<LogCollector.h>
#include<SnowServer.h>
#include"../protocol/TestProtocol.pb.h"
#include"PacketHandler.h"


class CIocpServer : public CSnowServer
{
private:
    std::atomic<uint32_t>           stSessionIndex_;
    std::vector<CSnowSession*>       vecSnowSession_;
public:
    CIocpServer(uint32_t workerThreadCount) :
        CSnowServer(workerThreadCount)
    {
    }

    void StartIocpServer(const char* pServerIP, const USHORT port)
    {
        vecSnowSession_.reserve(1000);
        StartSnowServer(pServerIP, port);
    }

    void CompletedAccpet(CSnowSession* pAcceptCompleteSession) override
    {
        if (pAcceptCompleteSession == nullptr)
        {
            PRINT_ERROR_LOG("pAcceptCompleteSession is nullptr\n");
            return;
        }

        PRINT_INFO_LOG(__FUNCTION__,"\n");
        vecSnowSession_.push_back(pAcceptCompleteSession);
        pAcceptCompleteSession->OnRecv();

    }
    virtual void CompletedSend(CSnowSession* pSendCompleteSession, const DWORD sendByte)override
    {
        PRINT_INFO_LOG(__FUNCTION__, "Send Byte: ", sendByte, "\n");

    }
    virtual void CompletedRecv(CSnowSession* pRecvCompleteSession, const DWORD recvByte)override
    {
        PRINT_INFO_LOG(__FUNCTION__, "Recv Byte: ", recvByte, "\n");
    }


    void EchoLoop()
    {

        /*for (const auto session : vecSnowSession_)
        {

            int32_t recvLen = session->OnRecv();

            TestProtocol::SC_LOING_RES cProtoBufferPacket;
            if (DegeneratedProtoBuf(&cProtoBufferPacket, session->GetRecvBuffer(), session->GetRecvBufferSize()) == true)
            {
                std::cout << "Recv: " << cProtoBufferPacket.sessionindex() << "\n";

                cProtoBufferPacket.set_sessionindex(cProtoBufferPacket.sessionindex() + 1);
                if (GeneratedProtoBuf(&cProtoBufferPacket, session->GetSendBuffer(), session->GetSendBufferSize(), PT::SC_LOING_RES) == true)
                {
                    session->OnSend();
                }
            }

        }*/
    }



};
