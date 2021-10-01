#pragma once

#include<vector>
#include<SnowSession.h>
#include<SnowThread.h>
#include<atomic>
#include<LogCollector.h>

#include"../protocol/TestProtocol.pb.h"
#include"PacketHandler.h"


#define SERVER_ADDDR "127.0.0.1"
constexpr int MAX_SESSION      = 10000;
constexpr int PORT             = 9000;

class CServer {
private:
    CSnowSocket                     accpetSocket_;
    CSnowThread                     accpetWaitThread_;
    std::vector<CSnowSession*>      vecSession_;
    std::atomic<uint32_t>           stSessionIndex_;
public:
    CServer() :
        accpetWaitThread_(&CServer::AcceptThread, this)
    {
        vecSession_.reserve(MAX_SESSION);
    }

    ~CServer()noexcept {
        WSACleanup();
    }

    void AcceptThread() {

        WSADATA stWSAData;
        // Initialize Winsock
        if (WSAStartup(MAKEWORD(2, 2), &stWSAData) != 0) {
            PRINT_ERROR_LOG("Can Not Load winsock.dll", WSAGetLastError());
        }

        accpetWaitThread_.ToglePrintThreadResponsiveTime();

        //Bind
        SOCKADDR_IN serverAddr;
        ZeroMemory(&serverAddr, sizeof(SOCKADDR_IN));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(PORT);
        inet_pton(AF_INET, SERVER_ADDDR, &serverAddr.sin_addr);

        accpetSocket_.InitSocket(SOCKET_TYPE::TCP_TYPE);
        if (accpetSocket_.Bind(&serverAddr) == false) return;
        if (accpetSocket_.Listen() == false)return;

        accpetSocket_.SetReuseAddr(true);

        while (true) {

            SOCKADDR_IN clinetInfo;
            ZeroMemory(&clinetInfo, sizeof(SOCKADDR_IN));

            auto tempSocket = accpetSocket_.Accept(reinterpret_cast<SOCKADDR*>(&clinetInfo));

            if (tempSocket != INVALID_SOCKET) {

                CSnowSession* tempSession = new CSnowSession(SOCKET_TYPE::TCP_TYPE, ++stSessionIndex_);
                tempSession->SetSocket(tempSocket);

                tempSession->SetSessionAdder(reinterpret_cast<PSOCKADDR>(&clinetInfo));
                PRINT_LOG("Accpet Session: ");
                tempSession->PrintSessionAddrInfor();
                vecSession_.push_back(tempSession);
            }
            else {
                PRINT_ERROR_LOG("Accpet Error", WSAGetLastError());
            }
        }
    }

    void EchoLoop() {

        for (const auto session : vecSession_) {

            int32_t recvLen = session->OnRecv();

            TestProtocol::SC_LOING_RES cProtoBufferPacket;
            if (DegeneratedProtoBuf(&cProtoBufferPacket, session->GetRecvBuffer(), session->GetRecvBufferSize()) == true) {
                std::cout<<"Recv: "<< cProtoBufferPacket.sessionindex() << "\n";
                
                cProtoBufferPacket.set_sessionindex(cProtoBufferPacket.sessionindex() + 1);
                if (GeneratedProtoBuf(&cProtoBufferPacket, session->GetSendBuffer(), session->GetSendBufferSize(), PT::SC_LOING_RES) == true) {
                    session->OnSend();
                }
            }

        }
    }

};