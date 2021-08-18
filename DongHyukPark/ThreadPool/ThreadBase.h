#pragma once

#include<chrono>
#include"WinHeader.h"

/*
- Thread�� ���̽��� �Ǵ� Ŭ����
- �ð� ���� 

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