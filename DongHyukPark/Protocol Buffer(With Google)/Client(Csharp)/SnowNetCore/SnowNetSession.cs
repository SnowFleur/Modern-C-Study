using System;
using System.Net.Sockets;
using System.Runtime.InteropServices;

/*
 - C# NetCore Base Session Class
 */

namespace SnowNetCore
{
    internal class CSnowNetSession
    {
        private Socket     socket_;
        private Byte[] arrBuffer_ { get; }

        public CSnowNetSession()
        {
            arrBuffer_ = new Byte[1024];
        }

        ~CSnowNetSession()
        {
            socket_.Close();
        }

        public bool ConnectToServer(string addr, int port)
        {
            socket_ = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            //Connect
            try
            {
                socket_.Connect(addr, port);
            }
            catch (SocketException ex)
            {
                Console.WriteLine(ex.Message);
            }

            if (socket_.Connected == true)
            {
                Console.WriteLine("The server connection was successful");
                return true;
            }
            else
            {
                Console.WriteLine("Can't Connection Server: Error:" + Marshal.GetLastWin32Error());
                return false;
            }
        }

        protected Int32 OnSend( byte[] arrPacket, Int32 packetSize)
        {
            return socket_.Send(arrPacket);
        }

        protected Int32 OnRecv()
        {
            return socket_.Receive(arrBuffer_);
        }
    }
}