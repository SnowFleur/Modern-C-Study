#pragma once

#include<chrono>
#include"WinHeader.h"

/*
- Thread의 베이스가 되는 클래스
- 시간 측정 

*/


class CThreadBase {
private:
    HANDLE      hThreadHandle_;

public:
    CThreadBase();
    ~CThreadBase()noexcept;

    CThreadBase(const CThreadBase&)             = delete;
    CThreadBase& operator=(const CThreadBase&)  = delete;
public:

    inline HANDLE  getHandle() { hThreadHandle_; }

    virtual void Run();
};