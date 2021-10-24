#pragma once
/*
- Developer: SnowFleur
- Descriptor: Task를 처리해줄 테스트용 Class
*/

#include"SnowThread.h"

class CWorkerThread : public CSnowThread
{
private:
    bool isRunning_;
public:
    CWorkerThread(uint64_t threadID);
    ~CWorkerThread() noexcept override;
public:
    uint32_t Excute(uint64_t threadID);

    inline void SetIsRunning(const bool isRun)   { isRunning_ = isRun; }
    inline bool GetIsRunning()const              { return isRunning_; }
};

