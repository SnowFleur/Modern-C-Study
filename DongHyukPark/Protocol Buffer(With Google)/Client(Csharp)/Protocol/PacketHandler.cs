/*
- Developer: PDH
- Descriptor: ProtoBuffer를 만들어주는 헬퍼함수(헬퍼뜻맞나?)
- To do 템플릿은 좀 더 C#을 공부하고 써야할듯 안된다..
- 다른 프로젝트에서는 쓰기 힘들듯
*/

using Google.Protobuf;
using System;
using System.Runtime.InteropServices;
using TestProtoBufProtocol;


namespace Client_Csharp_.Protocol
{
    using PacketSize = UInt16;

    internal enum PT : UInt16
    {
        CS_PT_BEGIN = 0,
        CS_LOING_REQ = CS_PT_BEGIN + 1,
        SC_LOING_RES,
        ECHO_SEND_MESSAGE,
        CS_PT_END,
    }

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    internal struct stPacketHeader
    {
        public PacketSize packetSize;
        public PT packetType;
    }

    internal class PacketHandler
    {
        public static Int32 Generated_CS_LOGIN_REQ(ref byte[] arrBuffer)
        {
            CS_LOGIN_REQ loginRes = new CS_LOGIN_REQ();

            stPacketHeader packetHeader = new stPacketHeader();
            packetHeader.packetType = PT.CS_LOING_REQ;
            packetHeader.packetSize = (UInt16)(loginRes.CalculateSize() + Marshal.SizeOf(typeof(stPacketHeader)));

            //헤더 카피
            IntPtr ptr = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(stPacketHeader)));
            Marshal.StructureToPtr(packetHeader, ptr, true);
            Marshal.Copy(ptr, arrBuffer, 0, Marshal.SizeOf(typeof(stPacketHeader)));

            //패킷카피
            Buffer.BlockCopy(loginRes.ToByteArray(), 0, arrBuffer, Marshal.SizeOf(typeof(stPacketHeader)), loginRes.CalculateSize());

            return packetHeader.packetSize;
        }


        public static stPacketHeader SplictPacketToHeader(ref byte[] arrBuffer, Int32 recvSize)
        {
            stPacketHeader packetHeader = new stPacketHeader();

            packetHeader.packetSize = BitConverter.ToUInt16(arrBuffer, 0);
            packetHeader.packetType = (PT)BitConverter.ToUInt16(arrBuffer, 2);

            return packetHeader;
        }

        public static _Ty DegenratedPrtoBufferPacket<_Ty>(ref byte[] arrBuffer, Int32 packetSize) where _Ty : IMessage<_Ty>, new()
        {
            if (packetSize < Marshal.SizeOf(typeof(stPacketHeader))) return new _Ty();

            MessageParser<_Ty> parser = new MessageParser<_Ty>(() => new _Ty());
            //개선 필요 
            return parser.ParseFrom(arrBuffer, Marshal.SizeOf(typeof(stPacketHeader)), packetSize - Marshal.SizeOf(typeof(stPacketHeader)));
        }

    }
}