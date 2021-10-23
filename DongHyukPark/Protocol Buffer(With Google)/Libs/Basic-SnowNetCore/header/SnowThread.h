#pragma once
/*
- Developer: PDH
- Descriptor: Thread를 캡슐화 하여 여러가지 기능을 가지는 클래스
-
*/

#include<chrono>
#include<functional>
#include"WindowsHeader.h"
#include<iostream>
using namespace std::chrono;

class CSnowThread 
{
    using CallBackFtn = std::function<uint32_t()>;
private:
    HANDLE                      hThreadHandle_;
    bool                        isAlive_;
    CallBackFtn                 cCallBackFuncion_;
#ifdef _WIN64
    DWORD    threadID_;
#else
    DWORD    threadID_;
#endif // _WIN64

    static  uint32_t __stdcall    OnInvoke(LPVOID arg)
    {
        if (reinterpret_cast<CSnowThread*>(arg) == nullptr) return 0;
        uint32_t returnValue = reinterpret_cast<CSnowThread*>(arg)->cCallBackFuncion_();
        _endthreadex(0);
        return returnValue;
    }

public:
    //상속확장가능
    virtual ~CSnowThread()noexcept;
    CSnowThread(const CSnowThread&) = delete;
    CSnowThread& operator=(const CSnowThread&) = delete;
    CSnowThread(CSnowThread&&)noexcept = delete;
    CSnowThread& operator=(CSnowThread&&) = delete;
public:

    /*여러 가지 기능들 */
    void        SetThreadPriority(const int32_t priority);
    int32_t     GetThreadPriority()const;
    void        ContextSwitch();
    void        WaitForThread();

    inline uint32_t    GetThreadID()const                 { return threadID_; }
    inline HANDLE      GetHandle()const                   { return hThreadHandle_; }
    inline void        SetThreadID(const DWORD ThreadID)  { threadID_ = ThreadID; }

    /*Template Functions*/
private:
    template<class _Ty, class... _Args>
    void Run(_Ty&& ftn, _Args&&... args)
    {
        cCallBackFuncion_ = std::bind(std::forward<_Ty>(ftn), std::forward<_Args>(args)...);
        hThreadHandle_ = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, OnInvoke, static_cast<void*>(this), 0, NULL));
    }
public:
    template<class _Ty, class... _Args>
    CSnowThread(_Ty&& ftn, _Args&&... args)
    {
        Run(std::forward<_Ty>(ftn), std::forward<_Args>(args)...);
    }
};
