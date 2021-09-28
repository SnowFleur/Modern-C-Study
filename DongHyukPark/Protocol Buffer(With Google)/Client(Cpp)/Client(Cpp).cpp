//Only Used x64
#ifdef _DEBUG
    #pragma comment(lib,"Debug\\Basic-SnowNetCore.lib")
    #pragma comment(lib,"Debug\\libprotobufd.lib")
#else
    #pragma comment(lib,"Release\\Basic-SnowNetCore.lib")
    #pragma comment(lib,"Release\\libprotobuf.lib")
#endif // _DEBUG

#define SERVER_ADDDR "127.0.0.1"
constexpr int PORT            = 9000;
const int BUFFER_SIZE         = 1024;
constexpr int MAX_PACKET_SIZE = 500;

#include<SnowSession.h>
#include<LogCollector.h>
//#include"../protocol/TestProtocol.pb.h"
#include"../protocol/Protocol.pb.h"
//#include"../Server/PacketHandler.h"


int main() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    WSADATA stWSAData;
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &stWSAData) != 0) {
        PRINT_ERROR_LOG("Can Not Load winsock.dll", WSAGetLastError());
    }

    CSnowSession session{ SOCKET_TYPE::TCP_TYPE,0,BUFFER_SIZE };

    //SERVER ADDR
    SOCKADDR_IN serverAddr;
    ZeroMemory(&serverAddr, sizeof(SOCKADDR_IN));

    serverAddr.sin_family   = AF_INET;
    serverAddr.sin_port     = PORT;
    inet_pton(AF_INET, SERVER_ADDDR, &serverAddr.sin_addr);

    Protocol::S_Test s;

    if (session.Connect(&serverAddr)) {
        PRINT_LOG("The server connection was successful");
        //Game Loop
        while (true) {
            Sleep(100);

            char packet[MAX_PACKET_SIZE]{};
            memset(packet, 0, MAX_PACKET_SIZE);


            //TestProtocol::CS_LOGIN_REQ cLoginReq;




            /*   if (GeneratedProtoBuf(&cGePacket, packet, sizeof(packet), TestProtocol::PT::PT_SC_LOING_RES) == true)
               {
                   int32_t sendLen = session.OnSend(packet);
               }*/

        }
    }
    else {
        PRINT_ERROR_LOG("Can't Connection Server");
    }
}