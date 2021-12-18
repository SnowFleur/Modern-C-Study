using TestProtoBufProtocol;
using SnowNetCore;
using Google.Protobuf;
using System;
using System.IO;
using Client_Csharp_.Protocol;

namespace Client_Csharp_
{
    class CGameSession : CSnowNetSession
    {

        public void Send_Login_REQ(ulong index)
        {
            Console.WriteLine("Send Byte: " + OnSend((PacketHandler.Generated_CS_LOGIN_REQ(index, ref arrBuffer_))));
        }
        public bool Recv()
        {
            Int32 recvByte = OnRecv();

            if (recvByte > 0)
            {
                return true;
            }
            return false;
        }

    }


}