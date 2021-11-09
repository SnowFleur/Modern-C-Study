#pragma once
#include"WindowsHeader.h"
#include"Buffer.h"

class CSnowSession;

enum class IO_EVENT : UINT8 
{
    RECV
   ,SEND
};

class OverlappedEx 
{
public:
    OVERLAPPED         overlapped_;
    WSABUF             wsabuf_;
    IO_EVENT           ioEvent_;
    CSnowSession*      pSession_;
    char               m_buffer[BUFFER_SIZE];

    OverlappedEx(CSnowSession* pSession, IO_EVENT io) : pSession_(nullptr), ioEvent_(io) 
    {
        ZeroMemory(&overlapped_, sizeof(overlapped_));
        pSession_ = pSession;
    }
};

class OverlappedSendEx : public OverlappedEx
{
public:
    OverlappedSendEx(CSnowSession* s) : OverlappedEx(s, IO_EVENT::SEND) {}
};

class OverlappedRecvEx : public OverlappedEx
{
public:
    OverlappedRecvEx(CSnowSession* s) : OverlappedEx(s, IO_EVENT::RECV) {}
};


class CIocpCore 
{
protected:
    HANDLE       hIocpHandle_;
public:
    CIocpCore() :
        hIocpHandle_(INVALID_HANDLE_VALUE)
    {
        hIocpHandle_ = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
        if (hIocpHandle_ == NULL)
        {
            std::cout << "Error: Can Not Init IOCP HANDLE\n";
        }
    }

    bool RegitIocp(SOCKET hSocket)
    {
        HANDLE resultHandle = CreateIoCompletionPort(reinterpret_cast<HANDLE>(hSocket), hIocpHandle_, NULL, NULL);

        if (resultHandle != hIocpHandle_)
            return false;

        return true;
    }

    void PQCS(DWORD ioByte, ULONG64 key, OverlappedEx* pOverEx)
    {
        if (pOverEx == nullptr) return;
        PostQueuedCompletionStatus(hIocpHandle_, ioByte, key, reinterpret_cast<OVERLAPPED*>(pOverEx));
    }

};