#pragma once
/*
- Developer: PDH
- Descriptor: Socket�� �پ��� ����� ĸ��ȭ�� Ŭ����  
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

    /*Linger�� CloseSocket�� ���� �� Send ���ۿ� ���� �����͸� ������ ���� ���ϴ� �ɼ� �Լ�*/
    inline bool SetLinger(UINT16 onoff, UINT16 linger) 
    {
        LINGER option{};
        option.l_onoff = onoff;
        option.l_linger = linger;
        return SetSocketOption(SO_LINGER, option);
    }

    /*Ŀ�ο� �ִ� SendBuffer ����� ���氡���� �ɼ� �Լ�*/
    inline bool SetSendBufferSize(INT32 bufferSize)
    {
        return SetSocketOption(SO_SNDBUF, bufferSize);
    }

    /*Ŀ�ο� �ִ� ReceiveBuffer ����� ���氡���� �ɼ� �Լ�*/
    inline bool SetReceiveBufferSize(INT32 bufferSize)
    {
        return SetSocketOption(SO_RCVBUF, bufferSize);
    }

    /*IP PORT�� ������ ������ �˷��ִ� �ɼ� �Լ� true=����, false=����X*/
    inline bool SetReuseAddr(bool flag)
    {
        return SetSocketOption(SO_REUSEADDR, flag);
    }

    /*���̱� �˰����� ����� ������ ���ϴ� �ɼ� �Լ� true=���̱� �� false=���̱� ���*/
    inline bool SetNagle(bool flag)
    {
        return SetSocketOption(TCP_NODELAY, flag);
    }

    /*�ֱ������� ���� ���¸� Ȯ���ϴ��� ���ϴ� �ɼ� �ռ�(����Ʈ ���� 2�ð�) true=���, false ���X*/
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

    /*LienSocket�� backlong�� ���� �Լ�true=���� false=��� */
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

