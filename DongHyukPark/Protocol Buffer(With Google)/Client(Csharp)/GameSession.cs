using Client_Csharp_.Protocol;
using SnowNetCore;
using System;

namespace Client_Csharp_
{
    internal class CGameSession : CSnowNetSession
    {
        public void Send_Login_REQ()
        {
            Console.WriteLine("Send Byte: " + OnSend((PacketHandler.Generated_CS_LOGIN_REQ(ref arrBuffer_))));
        }

        public bool Recv()
        {
            Int32 recvByte = OnRecv();

            if (recvByte > 0)
            {
                stPacketHeader header = PacketHandler.SplictPacketToHeader(ref arrBuffer_, recvByte);

                switch (header.packetType)
                {
                    case PT.SC_LOING_RES:
                        {
                            TestProtoBufProtocol.SC_LOING_RES packet = PacketHandler.DegenratedPrtoBufferPacket<TestProtoBufProtocol.SC_LOING_RES>(ref arrBuffer_, header.packetSize);
                            Console.WriteLine("Recv Session Index: " + packet.SessionIndex);
                            break;
                        }
                }
                return true;
            }
            return false;
        }
    }
}