#include"SnowThread.h"

CSnowThread::~CSnowThread()noexcept {
    if (hThreadHandle_ != INVALID_HANDLE_VALUE) {
        //PDH- Ŀ�� ��ü ��ȯ�� ������ �ƴ� �ʼ���.
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
        std::cout << "����\n";
    }

    _endthreadex(0);
    return 0;
}

/*���� ���� ��ɵ� */
void CSnowThread::SetPriorityThread() {

}

void CSnowThread::ContextSwitch() {

}

void CSnowThread::Join() {
    //TODO �����ϱ�
    Sleep(10000);
}

void CSnowThread::GetThreadID()const {

}

inline HANDLE  CSnowThread::getHandle() {
    return hThreadHandle_;
}
