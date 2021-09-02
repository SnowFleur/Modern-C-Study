#pragma once

#include<chrono>
#include<condition_variable>
#include<iostream>
#include<functional>
#include"WinHeader.h"

/*
- PDH
- Thread�� Ŭ������ ���� Ŭ����
- cpp ������ ������ �ʴ´�. ���ø��� ����ϱ⵵ �ϰ�...  �����? ---> ���ø��� ���⿡�� ����ϰ� cpp������
*/

using namespace std::chrono;

class CSnowThread {
    using CallBackFtn = std::function<void()>;
private:
    HANDLE                      hThreadHandle_;
    bool                        isAlive_;
    std::condition_variable     cEventHandle_;          //Spurious wakeup ����
    CallBackFtn                 cCallBackFuncion_;
#ifdef _WIN64
    uint64_t    threadID_;
#else
    uint32_t    threadID_;
#endif // _WIN64

    static  uint32_t __stdcall    OnInvoke(LPVOID arg) {
        return reinterpret_cast<CSnowThread*>(arg)->Thread();
    }
    uint32_t Thread();
public:
    virtual ~CSnowThread()noexcept;
    CSnowThread(const CSnowThread&)                 = delete;
    CSnowThread& operator=(const CSnowThread&)      = delete;
    CSnowThread(CSnowThread&&)noexcept              = delete;
    CSnowThread& operator=(CSnowThread&&)           = delete;
public:

    /*���� ���� ��ɵ� */
    void    SetPriorityThread();
    void    ContextSwitch();
    void    Join();
    void    GetThreadID()const;
    HANDLE  getHandle();

    /*Template Functions*/
private:
    template<class _Ty, class... _Args>
    void Run(_Ty&& ftn, _Args&&... args) {
        cCallBackFuncion_ = std::bind(std::forward<_Ty>(ftn), std::forward<_Args>(args)...);
        //TO DO Thread ID �ѱ��
        hThreadHandle_ = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, OnInvoke, static_cast<void*>(this), 0, NULL));
    }
public:
    template<class _Ty, class... _Args>
    CSnowThread(_Ty&& ftn, _Args&&... args) {
        Run(std::forward<_Ty>(ftn), std::forward<_Args>(args)...);
    }
};
