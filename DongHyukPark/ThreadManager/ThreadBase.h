#pragma once

#include<chrono>
#include"WinHeader.h"

/*
- Thread�� ���̽��� �Ǵ� Ŭ����
- �ð� ���� 

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

    /*���� ���� ��ɵ�*/
public:
    CThreadBase();
    ~CThreadBase()noexcept;

    CThreadBase(const CThreadBase&)             = delete;
    CThreadBase& operator=(const CThreadBase&)  = delete;
public:

    inline HANDLE  getHandle() { hThreadHandle_; }

    virtual void Run() = 0;
};