#pragma once
#include<stdint.h>
#include"WindowsHeader.h"
#include"DefineUtilty.h"

//Forward Declaration
class CSnowSession;
class CSnowSocket;
class CNetAddress;
class CSnowThread;
class CBuffer;


//Using Data type
#ifdef _WIN64
using SessionID     = uint64_t;
using ERROR_CODE    = uint64_t;
#else
using SessionID     = int32_t;
using ERROR_CODE    = int32_t;
#endif
using PacketType    = uint16_t;
using PacketSize    = uint16_t;

//*************************
//enum class
//*************************
enum class SOCKET_TYPE  : uint8_t{ TCP_TYPE = 1, UDP_TYPE };

//*************************
//Smart Pointer
//*************************


