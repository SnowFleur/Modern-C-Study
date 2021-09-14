#include<iostream>
#include"SnowThread.h"

CSnowThread::~CSnowThread()noexcept {
    if (hThreadHandle_ != INVALID_HANDLE_VALUE) {
        //PDH- 커널 객체 반환은 선택이 아닌 필수다.
        CloseHandle(hThreadHandle_);
    }
}

uint32_t CSnowThread::Thread() {
    try {

        while (true) {

            auto StartTime = high_resolution_clock::now();
            cCallBackFuncion_();
            auto EndTime = high_resolution_clock::now();
            auto ElapsedTime = duration_cast<milliseconds>(EndTime - StartTime).count();

            if (optionFlag_ & PRINT_THREAD_RESPONSIVE_TIME) {
                std::cout << "Thread Resonsive Time: " << ElapsedTime << "ms\n";
            }

        }
    }
    catch (std::exception& e) {
        std::cout << "망했다!" << e.what() << "\n";
    }

    _endthreadex(0);
    return 0;
}

/*여러 가지 기능들 */
void CSnowThread::SetThreadPriority(const int32_t priority) {
    if (::SetThreadPriority(hThreadHandle_, priority) == 0) {
        std::cout << "Can't Thread Priority: " << WSAGetLastError() << "\n";
    }
}

int32_t CSnowThread::GetThreadPriority() const {
    if (hThreadHandle_ == INVALID_HANDLE_VALUE)return -1;
    return ::GetThreadPriority(hThreadHandle_);
}

void CSnowThread::ContextSwitch() {}

void CSnowThread::Join() {
    //TODO 수정하기
    Sleep(10000);
}

uint32_t CSnowThread::GetThreadID()const {
    return -1;
}

HANDLE CSnowThread::GetHandle()const {
    return hThreadHandle_;
}

void CSnowThread::ToglePrintThreadResponsiveTime() {
    optionFlag_ ^= PRINT_THREAD_RESPONSIVE_TIME;
}
