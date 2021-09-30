#pragma once

/*
- Since: 2021 Year
- Description: Packet Header Class �� PT�� �����ϴ� Header
- TMI: ProtoBuffer�� �������� �ߴµ� ����� ���� ���°� ���� �� ����
*/

using PacketSize = unsigned __int16;

enum class PT : unsigned __int16 {
    CS_PT_BEGIN   = 0,
    CS_LOING_REQ  = CS_PT_BEGIN + 1,
    SC_LOING_RES,
    ECHO_SEND_MESSAGE,
    CS_PT_END,
};

#pragma push(1)
struct STPacketHeader {
public:
    PacketSize   packetSize;
    PT           packetType;

    STPacketHeader() :packetSize(0), packetType(PT::CS_PT_BEGIN) {}
    ~STPacketHeader()noexcept = default;
};
#pragma pop()