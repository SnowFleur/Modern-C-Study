using System;
using System.Net.Sockets;
using System.Net;
using System.Runtime.InteropServices;

namespace CSnowNetwork
{
    class CSnowNetSession
    {
        private Socket socket_;
        public CSnowNetSession() { }

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

        public bool SendMessage() { return true; }

        public bool RecvMesage() { return true; }

    }
}
