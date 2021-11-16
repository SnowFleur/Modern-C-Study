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


#include"DummyProcess.h"

int main()
{

    GOOGLE_PROTOBUF_VERIFY_VERSION;
    CDummyManager cDummyManager(1);
    cDummyManager.StartDummyManager(SERVER_ADDDR, PORT, 5);
}