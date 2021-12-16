using TestProtocol;
using SnowNetCore;
using Google.Protobuf;
using System;
using System.IO;

namespace Client_Csharp_
{
    class CGameSession : CSnowNetSession
    {

        public void Send_Login_REQ(ulong index)
        {
            SC_LOING_RES loginRes = new SC_LOING_RES();
            loginRes.SessionIndex = index;

            OnSend( loginRes.ToByteArray(), loginRes.CalculateSize());
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