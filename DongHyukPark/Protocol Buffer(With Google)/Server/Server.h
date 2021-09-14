#pragma once

#include<vector>
#include<SnowSession.h>
#include<SnowThread.h>
#include<atomic>


constexpr int MAX_SESSION = 10000;

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
            //PRINT_ERROR_LOG("Can Not Load winsock.dll", WSAGetLastError());
            std::cout << "Can Not Load winsock.dll\n";
        }

        accpetWaitThread_.ToglePrintThreadResponsiveTime();

        //Bind
        SOCKADDR_IN serverAddr;
        ZeroMemory(&serverAddr, sizeof(SOCKADDR_IN));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = PORT;
        inet_pton(AF_INET, SERVER_ADDDR, &serverAddr.sin_addr);

        accpetSocket_.InitSocket(SOCKET_TYPE::TCP_TYPE);
        if (accpetSocket_.Bind(&serverAddr) == false) return;
        if (accpetSocket_.Listen() == false)return;


        while (true) {

            SOCKADDR_IN clinetInfo;
            ZeroMemory(&clinetInfo, sizeof(SOCKADDR_IN));

            auto tempSocket = accpetSocket_.Accept(reinterpret_cast<SOCKADDR*>(&clinetInfo));

            if (tempSocket != INVALID_SOCKET) {

                CSnowSession* tempSession = new CSnowSession(SOCKET_TYPE::TCP_TYPE, ++stSessionIndex_, BUFFER_SIZE);
                tempSession->SetSocket(tempSocket);
                std::cout << "Accpet Session\n";
                vecSession_.push_back(tempSession);
                //TO DO NetAddr;
            }
            else {
                std::cout << WSAGetLastError() << "Accpet Error\n";
            }
        }
    }

};