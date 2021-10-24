#include"SnowThread.h"

CSnowThread::~CSnowThread()noexcept 
{
    if (hThreadHandle_ != INVALID_HANDLE_VALUE)
    {
        //PDH- Ŀ�� ��ü ��ȯ�� ������ �ƴ� �ʼ���.
        if (CloseHandle(hThreadHandle_) == TRUE)
        {
            hThreadHandle_ = NULL;
#ifdef  PRINT_THREAD_CLOSE_LOG
            PRINT_INFO_LOG("Sucess Close Thread Handle",
                "ThreadID: ",threadID_,"\n");
#endif 
        }
        else
        {
            PRINT_ERROR_LOG("Thread Close Handle", WSAGetLastError(),"\n");
        }
    }
}

/*���� ���� ��ɵ� */
void CSnowThread::SetThreadPriority(const int32_t priority) 
{
    if (::SetThreadPriority(hThreadHandle_, priority) == 0)
    {
        std::cout << "Can't Thread Priority: " << WSAGetLastError() << "\n";
    }
}

int32_t CSnowThread::GetThreadPriority() const 
{
    if (hThreadHandle_ == INVALID_HANDLE_VALUE)return -1;
    return ::GetThreadPriority(hThreadHandle_);
}

void CSnowThread::ContextSwitch() {}

void CSnowThread::WaitForThread()
{
    WaitForSingleObject(hThreadHandle_, INFINITE);
}

