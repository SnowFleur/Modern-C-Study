#pragma once

/*
- [2021.09.24]
- ProtoBuffer packet 를 만들어주는 Packet Handler 
- To do 좀더 자동화 와 제네릭처리를 하고싶다.
- To do 유효성 검증 추가
*/

class CPacketHandler {
public:
    
    template<class _Ty, class _PT>
    static bool GeneratedProtoBufferPacket(_Ty* sourceData, char* destData, const size_t destSize, _PT packetType) {

        if (sourceData->ByteSizeLong() == 0) return false;
        if (sourceData == nullptr)     return false;
        if (destData == nullptr)       return false;
        if (destSize <= 0)             return false;

        sourceData->set_packetsize(sourceData->ByteSizeLong());
        sourceData->set_packettype(packetType);
        if (sourceData->SerializePartialToArray(destData, destSize) == false) return false;
        return true;
    }

    template<class _Ty>
    static bool DegenerateProtoBufferPacket(_Ty* destData, const char* sourceData, const size_t sourceDataSize) {

        if (sourceData == nullptr) return false;
        if (destData == nullptr)   return false;
        if (sourceDataSize <= 0)   return false;
        if (destData->ParseFromArray(sourceData, sourceDataSize) == false) return false;
        return true;
    }

};

#define GeneratedProtoBuf    CPacketHandler::GeneratedProtoBufferPacket
#define DegeneratedProtoBuf  CPacketHandler::DegenerateProtoBufferPacket