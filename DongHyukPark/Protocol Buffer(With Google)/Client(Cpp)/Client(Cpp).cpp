//Only Used x64
#ifdef _DEBUG
    #pragma comment(lib,"Debug\\Basic-SnowNetCore.lib")
    #pragma comment(lib,"Debug\\libprotobufd.lib")
#else
    #pragma comment(lib,"Release\\Basic-SnowNetCore.lib")
    #pragma comment(lib,"Release\\libprotobuf.lib")
#endif // _DEBUG

#define PROTOBUF_USE_DLLS
#define SERVER_ADDDR "127.0.0.1"
constexpr int PORT            = 9000;

#include<SnowSession.h>
#include<LogCollector.h>

#include"../Server/PacketHandler.h"
#include"../protocol/TestProtocol.pb.h"

int main() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    WSADATA stWSAData;
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &stWSAData) != 0) {
        PRINT_ERROR_LOG("Can Not Load winsock.dll", WSAGetLastError());
    }

    CSnowSession session{ SOCKET_TYPE::TCP_TYPE,0};

    //SERVER ADDR
    SOCKADDR_IN serverAddr;
    ZeroMemory(&serverAddr, sizeof(SOCKADDR_IN));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port   = htons(PORT);
    inet_pton(AF_INET, SERVER_ADDDR, &serverAddr.sin_addr);


    if (session.Connect(&serverAddr)) {
        PRINT_LOG("The server connection was successful");

        TestProtocol::SC_LOING_RES cProtoBufferPacket;
        cProtoBufferPacket.set_sessionindex(15);

        if (GeneratedProtoBuf(&cProtoBufferPacket, session.GetSendBuffer(), session.GetSendBufferSize(), PT::SC_LOING_RES) == true) {
            int32_t sendByte = session.OnSend();
            PRINT_LOG("Send Byte:", sendByte);
        }
        else {
            PRINT_ERROR_LOG("Packet Generate");
        }

        //Game Loop
        while (true) {
            Sleep(100);
            if (session.OnRecv()) {
                if (DegeneratedProtoBuf(&cProtoBufferPacket, session.GetRecvBuffer(), session.GetRecvBufferSize()) == true) {
                    std::cout << "Recv: " << cProtoBufferPacket.sessionindex() << "\n";

                    cProtoBufferPacket.set_sessionindex(cProtoBufferPacket.sessionindex() + 1);
                    if (GeneratedProtoBuf(&cProtoBufferPacket, session.GetSendBuffer(), session.GetSendBufferSize(), PT::SC_LOING_RES) == true) {
                        session.OnSend();
                    }
                }
            }
        }
    }
    else {
        PRINT_ERROR_LOG("Can't Connection Server");
    }
}