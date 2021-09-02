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
        }
    }
    catch (std::exception& e) {
        std::cout << "쉬벌\n";
    }

    _endthreadex(0);
    return 0;
}

/*여러 가지 기능들 */
void CSnowThread::SetPriorityThread() {

}

void CSnowThread::ContextSwitch() {

}

void CSnowThread::Join() {
    //TODO 수정하기
    Sleep(10000);
}

void CSnowThread::GetThreadID()const {

}

inline HANDLE  CSnowThread::getHandle() {
    return hThreadHandle_;
}
