//Only Used x64
#ifdef _DEBUG
    #pragma comment(lib,"Debug\\Basic-SnowNetCore.lib")
    #pragma comment(lib,"Debug\\libprotobufd.lib")
#else
    #pragma comment(lib,"Release\\Basic-SnowNetCore.lib")
    #pragma comment(lib,"Release\\libprotobuf.lib")
#endif // _DEBUG

#include<SnowSession.h>

#define SERVER_ADDDR "127.0.0.1"
constexpr int PORT      = 9000;
const int BUFFER_SIZE   = 1024;

int main() {

    WSADATA stWSAData;
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &stWSAData) != 0) {
        //PRINT_ERROR_LOG("Can Not Load winsock.dll", WSAGetLastError());
        std::cout << "Can Not Load winsock.dll\n";
    }

    CSnowSession session{ SOCKET_TYPE::TCP_TYPE,0,BUFFER_SIZE };

    //SERVER ADDR
    SOCKADDR_IN serverAddr;
    ZeroMemory(&serverAddr, sizeof(SOCKADDR_IN));

    serverAddr.sin_family   = AF_INET;
    serverAddr.sin_port     = PORT;
    inet_pton(AF_INET, SERVER_ADDDR, &serverAddr.sin_addr);

    if (session.Connect(&serverAddr)) {
        std::cout << "The server connection was successful \n";
        //Game Loop
        while (true) {
            Sleep(100);
        }
    }
    else {
        std::cout << "Can't Connection Server\n";

    }
}