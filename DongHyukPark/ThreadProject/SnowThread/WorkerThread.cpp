#include "WorkerThread.h"
#include"LogCollector.h"
CWorkerThread::CWorkerThread(uint64_t threadID) :
    CSnowThread(&CWorkerThread::Excute, this, threadID)
    , isRunning_(true)
{
}

CWorkerThread::~CWorkerThread() noexcept
{
    PRINT_INFO_LOG("Called Destructor Thread Number: ",GetThreadID(),"\n");
}

uint32_t CWorkerThread::Excute(uint64_t threadID)
{
    SetThreadID(threadID);

    while (isRunning_)
    {
        Sleep(100);
        PRINT_LOG("My Thread Number: ", GetThreadID(), "\n");
    }
    return 0;
}
