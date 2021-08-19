#pragma once

#include<chrono>
#include"WinHeader.h"

/*
- Thread의 베이스가 되는 클래스
- 시간 측정 

*/

using namespace std::chrono;

class CThreadBase {
private:
    HANDLE      hThreadHandle_;
#ifdef _WIN64
    uint64_t    threadID_;
#else
    uint32_t    threadID_;
#endif // _WIN64

    /*여러 가지 기능들*/
public:
    CThreadBase();
    ~CThreadBase()noexcept;

    CThreadBase(const CThreadBase&)             = delete;
    CThreadBase& operator=(const CThreadBase&)  = delete;
public:

    inline HANDLE  getHandle() { hThreadHandle_; }

    virtual void Run() = 0;
};