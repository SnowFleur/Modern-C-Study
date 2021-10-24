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

    srand(GetCurrentTime());

    int32_t endCount = rand() % 100;
    int32_t count = 0;

    while (isRunning_)
    {
        if (count >= endCount)
        {
            isRunning_ = false;
        }

        Sleep(100);
        //PRINT_LOG("My Thread Number: ", GetThreadID(), "\n");
        ++count;
    }

    std::cout << "=================================\n";
    PRINT_LOG("End My Thread Number: ", GetThreadID(), "\n");


    return 0;
}
