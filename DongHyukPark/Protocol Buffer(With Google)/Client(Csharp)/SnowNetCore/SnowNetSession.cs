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
        private Socket socket_;
        protected Byte[] arrBuffer_;

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

        protected Int32 OnSend(Int32 PacketSize)
        {
            Int32 sendByte = -1;
            try
            {
                sendByte = socket_.Send(arrBuffer_, PacketSize, SocketFlags.None);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }

            return sendByte;
        }

        protected Int32 OnRecv()
        {
            return socket_.Receive(arrBuffer_);
        }
    }
}