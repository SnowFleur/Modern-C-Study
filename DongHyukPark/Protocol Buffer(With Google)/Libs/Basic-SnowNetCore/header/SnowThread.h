#pragma once

#include<chrono>
#include<condition_variable>
#include<functional>

#include"WindowsHeader.h"

/*
- PDH
- Thread를 클래스로 감싼 클래스
- 템플릿은 h에 나머지는 cpp에
*/

using namespace std::chrono;

class CSnowThread {
    using CallBackFtn = std::function<void()>;
private:
    HANDLE                      hThreadHandle_;
    bool                        isAlive_;
    std::condition_variable     cEventHandle_;          //Spurious wakeup 방지
    CallBackFtn                 cCallBackFuncion_;
#ifdef _WIN64
    uint64_t    threadID_;
#else
    uint32_t    threadID_;
#endif // _WIN64

    static  unsigned __stdcall    OnInvoke(LPVOID arg) {
        return reinterpret_cast<CSnowThread*>(arg)->Thread();
    }
    uint32_t Thread();
public:
    virtual ~CSnowThread()noexcept {
        if (hThreadHandle_ != INVALID_HANDLE_VALUE) {
            //PDH- 커널 객체 반환은 선택이 아닌 필수다.
            CloseHandle(hThreadHandle_);
        }
    }

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
    HANDLE      getHandle()const;

    /*Template Functions*/
private:
    template<class _Ty, class... _Args>
    void Run(_Ty&& ftn, _Args&&... args) {
        cCallBackFuncion_ = std::bind(std::forward<_Ty>(ftn), std::forward<_Args>(args)...);
        //TO DO Thread ID 넘기기
        hThreadHandle_ = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, OnInvoke, static_cast<void*>(this), 0, NULL));
    }
public:
    template<class _Ty, class... _Args>
    CSnowThread(_Ty&& ftn, _Args&&... args):
    hThreadHandle_(INVALID_HANDLE_VALUE),
    isAlive_(false)
    {
        Run(std::forward<_Ty>(ftn), std::forward<_Args>(args)...);
    }
};
