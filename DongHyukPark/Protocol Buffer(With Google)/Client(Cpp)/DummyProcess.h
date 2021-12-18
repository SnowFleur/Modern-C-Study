#pragma once
/*
- Developer: PDH
- Descriptor: Dummy 클라이언트 역할을 수행하는 Class
- ProtoBuf 확인용 심플 클라임
*/



#include<atomic>
#include<SnowServer.h>

#include"../Server/PacketHandler.h"
#include"../protocol/TestProtoBufProtocol.pb.h"

class CDummyManager : public CSnowServer
{
private:
    std::atomic<uint32_t>           atSessionIndex;
    std::vector<CSnowSession*>      vecDummySession_;
public:
    CDummyManager(uint32_t workerThreadCount, bool isStartThread, const char* pServerIP, const USHORT port) :
        CSnowServer(pServerIP, port)
        , atSessionIndex(0)
    {
        vecDummySession_.reserve(1000);
        CSnowServer::CreateWorkerTherad(workerThreadCount, isStartThread);
    }

    virtual ~CDummyManager()noexcept override
    {
        for (auto iter = vecDummySession_.begin(); iter != vecDummySession_.end(); ++iter)
        {
            SAFE_DELETE(*iter);
        }
        vecDummySession_.clear();
    }

    void StartDummyManager(const char* pServerIP,USHORT port, uint32_t dummyCount)
    {
        PRINT_INFO_LOG("Start DummyManager\n");

        StartWorkerThread();


        //SERVER ADDR
        SOCKADDR_IN serverAddr;
        ZeroMemory(&serverAddr, sizeof(SOCKADDR_IN));
        
        // To do 라이브러리에서 어드레서 관련해서 접근이 불가능하네... 
        // 지금은 그냥.. 이렇게 하자. 언젠간 바꾸겠지  ㅎㅎㅎ
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        inet_pton(AF_INET, pServerIP, &serverAddr.sin_addr);

        for (uint32_t i = 0; i < dummyCount; ++i)
        {
            CSnowSession* pDummySession = nullptr;
            pDummySession = new CSnowSession{ SOCKET_TYPE::TCP_TYPE ,++atSessionIndex };

            if (pDummySession == nullptr) continue;


            if (pDummySession->OnConnect(  &serverAddr) == true)
            {
                PRINT_LOG("The server connection was successful\n");
                vecDummySession_.emplace_back(std::move(pDummySession));

                TestProtoBufProtocol::CS_LOGIN_REQ cProtoBufferPacket;
                cProtoBufferPacket.set_sessionindex(15);

                RegitIocp(pDummySession->GetSocket());

                if (GeneratedProtoBuf(&cProtoBufferPacket, pDummySession->GetSendBuffer(), pDummySession->GetSendBufferSize(), PT::SC_LOING_RES) == true)
                {
                    int32_t sendByte = pDummySession->OnSend();
                    PRINT_LOG("Send Byte:", sendByte,"\n");
                }
                else
                {
                    PRINT_ERROR_LOG("Packet Generate\n");
                }
            }
        }
        WaitForWorkerThread();
    }
 
       //overrride Funcions
public:
    void CompletedAccpet(CSnowSession* pAcceptCompleteSession) override{}

    virtual void CompletedSend(CSnowSession* pSendCompleteSession, const DWORD sendByte)override
    {
        PRINT_INFO_LOG(__FUNCTION__, "Send SessionID:", pSendCompleteSession->GetSessionID(), " Send Byte: ", sendByte, "\n");
        pSendCompleteSession->OnRecv();
    }

    virtual void CompletedRecv(CSnowSession* pRecvCompleteSession, const DWORD recvByte)override
    {
        PRINT_INFO_LOG(__FUNCTION__, "Recv SessionID:", pRecvCompleteSession->GetSessionID(), " Recv Byte: ", recvByte, "\n");
        TestProtoBufProtocol::CS_LOGIN_REQ cProtoBufferPacket;
        if (DegeneratedProtoBuf(&cProtoBufferPacket, pRecvCompleteSession->GetRecvBuffer(), pRecvCompleteSession->GetRecvBufferSize()) == true)
        {
            cProtoBufferPacket.set_sessionindex(cProtoBufferPacket.sessionindex() + 1);
            if (GeneratedProtoBuf(&cProtoBufferPacket, pRecvCompleteSession->GetSendBuffer(), pRecvCompleteSession->GetSendBufferSize(), PT::SC_LOING_RES) == true)
            {
                pRecvCompleteSession->OnSend();
            }
        }
    }


};
