#pragma once

#include<memory>
#include<vector>
#include"WindowsHeader.h"
#include"SnowSession.h"
#include"IocpCore.h"
#include"SnowThread.h"

using UptrSnowThread   = std::unique_ptr<CSnowThread>;

class CSnowServer : public CIocpCore
{
    const uint32_t WORERK_THREAD_ID = 1000;
private:
    uint32_t                          workerThreadCount_;
    std::vector<UptrSnowThread>       vecWorkerThread_;
    CNetAddress                       netAddress_;
public:
    CSnowServer(const char* pServerIP, const USHORT port);
    virtual ~CSnowServer()noexcept;

    CSnowServer(const CSnowServer&)                 = delete;
    CSnowServer& operator=(const CSnowServer&)      = delete;
    CSnowServer(CSnowServer&&)noexcept              = delete;
    CSnowServer& operator=(CSnowServer&&) noexcept  = delete;

protected:
    void StartSnowServer();
    bool CreateWorkerTherad(const uint32_t threadCount, const bool isStartThread);
    void StartWorkerThread();
    void WaitForWorkerThread();
public:

    uint32_t ExcuteWorkerThread();

    virtual void CompletedAccpet(CSnowSession* pAcceptCompleteSession) = 0;
    virtual void CompletedSend(CSnowSession* pSendCompleteSession, const DWORD sendByte) = 0;
    virtual void CompletedRecv(CSnowSession* pRecvCompleteSession, const DWORD recvByte) = 0;
};
