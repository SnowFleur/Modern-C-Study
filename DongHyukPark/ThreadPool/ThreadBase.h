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