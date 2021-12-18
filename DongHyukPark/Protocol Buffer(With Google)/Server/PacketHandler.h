#pragma once

/*
- [2021.09.24]
- ProtoBuffer packet �� ������ִ� Packet Handler
- To do ���� �ڵ�ȭ �� ���׸�ó���� �ϰ�ʹ�.
- To do ��ȿ�� ���� �߰�
*/

#include"PacketHeader.h"

class CPacketHandler {
public:

	template<class _Ty, class _PT>
	static bool GeneratedProtoBufferPacket(_Ty* sourceData, char* destData, const int32_t destSize, _PT packetType) {
		// if (sourceData->ByteSizeLong() == 0) return false;
		if (sourceData == nullptr)           return false;
		if (destData == nullptr)             return false;
		if (destSize <= 0)                   return false;

		unsigned short packetSize = static_cast<unsigned short>(sourceData->ByteSizeLong()) + sizeof(stPacketHeader);
		if (destSize < packetSize)           return false;

		stPacketHeader header{};
		header.packetSize = packetSize;
		header.packetType = packetType;
		memcpy_s(destData, destSize, &header, sizeof(stPacketHeader));
		return  sourceData->SerializePartialToArray(destData + sizeof(stPacketHeader), destSize);
	}

	template<class _Ty>
	static bool DegenerateProtoBufferPacket(_Ty* destData, const char* sourceData, const int32_t sourceDataSize) {
		if (sourceData == nullptr) return false;
		if (destData == nullptr)   return false;
		if (sourceDataSize <= 0)   return false;

		stPacketHeader header{};
		memcpy_s(&header, sizeof(stPacketHeader), sourceData, sizeof(stPacketHeader) > sourceDataSize ? sourceDataSize : sizeof(stPacketHeader));
		return  destData->ParseFromArray(sourceData + sizeof(stPacketHeader), header.packetSize - sizeof(stPacketHeader));
	}
};

#define GeneratedProtoBuf    CPacketHandler::GeneratedProtoBufferPacket
#define DegeneratedProtoBuf  CPacketHandler::DegenerateProtoBufferPacket