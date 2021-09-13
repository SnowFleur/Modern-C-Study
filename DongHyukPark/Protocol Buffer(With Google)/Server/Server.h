#pragma once

#include<SnowSession.h>
#include<SnowThread.h>

class CServer {
private:
    CSnowSocket                 accpetSocket_;
    CSnowThread                 accpetWaitThread_;
public:
    CServer():
        accpetWaitThread_(&CServer::AccpetThread, this),
        accpetSocket_(SOCKET_TYPE::TCP_TYPE)
    {
    }

    ~CServer()noexcept {}

    void AccpetThread() {
        std::cout << "Start Accpet Thread\n";
        while (true)Sleep(1000);
    }

};