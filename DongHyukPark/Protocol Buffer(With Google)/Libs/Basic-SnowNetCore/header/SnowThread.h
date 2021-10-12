#pragma once

#include<chrono>
#include<condition_variable>
#include<functional>
#include"WindowsHeader.h"

/*
-   [2021.08.19]
-   Thread의 다양한 기능을 캡슐화한 Class
-   C++11의 std::thread가 아닌 Windows _BeginThreadEX 사용
-   템플릿은 h 나머지는 cpp에
*/

using namespace std::chrono;

class CSnowThread
{
    using   CallBackFtn       = std::function<void()>;
    using   ThreadOptionFlag  = unsigned char;
    const   ThreadOptionFlag PRINT_THREAD_RESPONSIVE_TIME = 0x0001;
private:
    HANDLE                      hThreadHandle_;
    bool                        isAlive_;
    std::condition_variable     cEventHandle_;          //Spurious wakeup 방지
    CallBackFtn                 cCallBackFuncion_;
    ThreadOptionFlag            optionFlag_;
#ifdef _WIN64
    uint64_t    threadID_;
#else
    uint32_t    threadID_;
#endif // _WIN64

    static  unsigned __stdcall    OnInvoke(LPVOID arg) 
    {
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
    /*여러 가지 기능들 */
    void        SetThreadPriority(const int32_t priority);
    int32_t     GetThreadPriority()const;
    void        ContextSwitch();
    void        Join();
    uint32_t    GetThreadID()const;
    HANDLE      GetHandle()const;
    void        ToglePrintThreadResponsiveTime();

    /*Template Functions*/
private:
    template<class _Ty, class... _Args>
    void Run(_Ty&& ftn, _Args&&... args)
    {
        cCallBackFuncion_ = std::bind(std::forward<_Ty>(ftn), std::forward<_Args>(args)...);
        //TO DO Thread ID 넘기기
        hThreadHandle_ = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, OnInvoke, static_cast<void*>(this), 0, NULL));
    }
public:
    template<class _Ty, class... _Args>
    CSnowThread(_Ty&& ftn, _Args&&... args) :
        hThreadHandle_(INVALID_HANDLE_VALUE),
        isAlive_(false),
        optionFlag_(0)
    {
        Run(std::forward<_Ty>(ftn), std::forward<_Args>(args)...);
    }
};
