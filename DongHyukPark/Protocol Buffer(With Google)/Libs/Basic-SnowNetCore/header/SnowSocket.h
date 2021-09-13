#pragma once
#include<iostream>
#include"WindowsHeader.h"
#include"DataTypes.h"

/*
-   [2021.06.16]
-   Socket�� �پ��� ����� ĸ��ȭ�� Class  
- 
-
*/

class CSnowSocket {
private:
    SOCKET      socket_;
public:
    CSnowSocket(SOCKET_TYPE socketType, DWORD dwFlags = NULL) :
        socket_(INVALID_SOCKET)
    {
        switch (socketType) {
        case SOCKET_TYPE::TCP_TYPE:
            socket_ = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, dwFlags);
            break;
        case SOCKET_TYPE::UDP_TYPE:
            socket_ = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, dwFlags);
            break;
        default:
            break;
        }
        if (socket_ == INVALID_SOCKET) {
            std::cout << "Can Not Init Socket"<<WSAGetLastError()<<"\n";
        }
    }
    virtual ~CSnowSocket()noexcept {
        if (socket_ != INVALID_SOCKET)
            closesocket(socket_);
    }
public:

    inline SOCKET GetSocket()const { return socket_; }

    /*Linger�� CloseSocket�� ���� �� Send ���ۿ� ���� �����͸� ������ ���� ���ϴ� �ɼ� �Լ�*/
    inline bool SetLinger(UINT16 onoff, UINT16 linger) {
        LINGER option{};
        option.l_onoff  = onoff;
        option.l_linger = linger;
        return SetSocketOption(SO_LINGER, option);
    }

    /*Ŀ�ο� �ִ� SendBuffer ����� ���氡���� �ɼ� �Լ�*/
    inline bool SetSendBufferSize(INT32 bufferSize) {
        return SetSocketOption(SO_SNDBUF, bufferSize);
    }

    /*Ŀ�ο� �ִ� ReceiveBuffer ����� ���氡���� �ɼ� �Լ�*/
    inline bool SetReceiveBufferSize(INT32 bufferSize) {
        return SetSocketOption(SO_RCVBUF, bufferSize);
    }

    /*IP PORT�� ������ ������ �˷��ִ� �ɼ� �Լ� true=����, false=����X*/
    inline bool SetReuseAddr(bool flag) {
        return SetSocketOption(SO_REUSEADDR, flag);
    }

    /*���̱� �˰����� ����� ������ ���ϴ� �ɼ� �Լ� true=���̱� �� false=���̱� ���*/
    inline bool SetNagle(bool flag) {
        return SetSocketOption(TCP_NODELAY, flag);
    }

    /*�ֱ������� ���� ���¸� Ȯ���ϴ��� ���ϴ� �ɼ� �ռ�(����Ʈ ���� 2�ð�) true=���, false ���X*/
    inline bool SetKeepAlive(bool flag) {
        return SetSocketOption(SO_KEEPALIVE, flag);
    }

    /*LienSocket�� backlong�� ���� �Լ�true=���� false=��� */
    inline bool SetConditionalAccpet(bool flag) {
        return SetSocketOption(SO_CONDITIONAL_ACCEPT, flag);
    }

    bool    Bind(const SOCKADDR_IN* sockAddrIn);
    bool    Connect(const SOCKADDR_IN* serverAddr);
    SOCKET  Accept(const SOCKADDR* socketAddr);
    bool    Listen();
    bool    Close();

private:
    template<class _Ty>
    bool inline SetSocketOption(INT32 name, _Ty option) {
        return setsockopt(socket_, SOL_SOCKET, name, reinterpret_cast<char*>(&option), sizeof(option)) == SOCKET_ERROR ? false : true;
    }
};

