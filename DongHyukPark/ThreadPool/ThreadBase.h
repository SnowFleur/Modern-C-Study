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