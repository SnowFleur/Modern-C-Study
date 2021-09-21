/*
-
-   Proto Buffer 테스트용 C#(클라이언트) BasicSnowNetCore는 사용하지 않고 
-   C#에서 제공하는 Net Socket 사용
-
*/

using System;
using System.Net.Sockets;
using System.Net;
using CSnowNetwork;

namespace Client_Csharp_
{

    class Program
    {
        const string SERVER_ADDR    = "127.0.0.1";
        const int PORT              = 9000;

        CSnowNetSession session_;

        static void Main(string[] args)
        {
            Program pg = new Program();
            pg.Start();
        }

        void Start() 
        {
            Console.WriteLine("Start!!");

            session_ = new CSnowNetSession();
            session_.ConnectToServer(SERVER_ADDR, PORT);

            while (true) { };
        
        }

    }
}
