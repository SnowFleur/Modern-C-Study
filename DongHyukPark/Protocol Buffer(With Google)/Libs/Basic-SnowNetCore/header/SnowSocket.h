#pragma once
/*
- Developer: PDH
- Descriptor: Socket의 다양한 기능을 캡슐화한 클래스  
-
*/
#include"WindowsHeader.h"
#include"LogCollector.h"
#include"DataTypes.h"

class CSnowSocket 
{
private:
    SOCKET      socket_;
public:
    CSnowSocket(SOCKET_TYPE socketType) :
        socket_(INVALID_SOCKET)
    {
        switch (socketType) {
        case SOCKET_TYPE::TCP_TYPE:
            socket_ = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
            break;
        case SOCKET_TYPE::UDP_TYPE:
            socket_ = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);
            break;
        default:
            break;
        }
        if (socket_ == INVALID_SOCKET) {
            PRINT_ERROR_LOG("Can Not Init Socket", WSAGetLastError());
        }
    }
    ~CSnowSocket()noexcept {
        if (socket_ != INVALID_SOCKET)
            closesocket(socket_);
    }
public:

    inline SOCKET GetSocket()const { return socket_; }
    bool    Bind(const SOCKADDR_IN* sockAddrIn);
    bool    Bind(const char* IP, const USHORT port, const USHORT sinFamily);
    bool    Connect(const SOCKADDR_IN* serverAddr);
    SOCKET  Accept(const SOCKADDR* socketAddr);
    bool    Listen();
    bool    Close();
    bool    Shutdown();

    /*Linger는 CloseSocket을 했을 때 Send 버퍼에 남은 데이터를 보낼지 말지 정하는 옵션 함수*/
    inline bool SetLinger(UINT16 onoff, UINT16 linger) 
    {
        LINGER option{};
        option.l_onoff = onoff;
        option.l_linger = linger;
        return SetSocketOption(SO_LINGER, option);
    }

    /*커널에 있는 SendBuffer 사이즈를 변경가능한 옵션 함수*/
    inline bool SetSendBufferSize(INT32 bufferSize)
    {
        return SetSocketOption(SO_SNDBUF, bufferSize);
    }

    /*커널에 있는 ReceiveBuffer 사이즈를 변경가능한 옵션 함수*/
    inline bool SetReceiveBufferSize(INT32 bufferSize)
    {
        return SetSocketOption(SO_RCVBUF, bufferSize);
    }

    /*IP PORT를 재사용할 것인지 알려주는 옵션 함수 true=재사용, false=재사용X*/
    inline bool SetReuseAddr(bool flag)
    {
        return SetSocketOption(SO_REUSEADDR, flag);
    }

    /*네이글 알고리즘을 사용할 것인지 정하는 옵션 함수 true=네이글 끔 false=네이글 사용*/
    inline bool SetNagle(bool flag)
    {
        return SetSocketOption(TCP_NODELAY, flag);
    }

    /*주기적으로 연결 상태를 확인하는지 정하는 옵션 합수(디폴트 값은 2시간) true=허용, false 사용X*/
    inline bool SetKeepAlive(bool onoff, UINT32 checkmsTime, UINT32 interValmsTime)
    {
        tcp_keepalive tcpkl;
        ZeroMemory(&tcpkl, sizeof(tcpkl));
        DWORD dwTemp;
        tcpkl.onoff             = onoff;
        tcpkl.keepalivetime     = checkmsTime;
        tcpkl.keepaliveinterval = interValmsTime;

        // return setsockopt(socket_, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, reinterpret_cast<char*>(&tcpkl), sizeof(tcpkl));
        // return SetSocketOption(SO_UPDATE_ACCEPT_CONTEXT, tcpkl);
        return WSAIoctl(socket_, SIO_KEEPALIVE_VALS, &tcpkl, sizeof(tcp_keepalive), 0, 0, &dwTemp, NULL, NULL) == 0 ? true : false;
    }

    /*LienSocket의 backlong를 막는 함수true=막기 false=허용 */
    inline bool SetConditionalAccpet(bool flag) 
    {
        return SetSocketOption(SO_CONDITIONAL_ACCEPT, flag);
    }
private:
    template<class _Ty>
    bool inline SetSocketOption(INT32 name, _Ty option) 
    {
        return setsockopt(socket_, SOL_SOCKET, name, reinterpret_cast<char*>(&option), sizeof(option)) == SOCKET_ERROR ? false : true;
    }
};

