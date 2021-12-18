/*
-
-   Proto Buffer 테스트용 C#(클라이언트) BasicSnowNetCore는 사용하지 않고
-   C#에서 제공하는 Net Socket 사용
-
*/

using System;
using System.Threading;

namespace Client_Csharp_
{
    internal class Program
    {
        private const string SERVER_ADDR = "127.0.0.1";
        private const int PORT = 9000;

        private CGameSession gameSession_;

        private static void Main(string[] args)
        {
            Program pg = new Program();
            pg.Start();
        }

        private void Start()
        {
            Console.WriteLine("Start!!");
            gameSession_ = new CGameSession();

            bool isConnect = gameSession_.ConnectToServer(SERVER_ADDR, PORT);

            if (isConnect == true)
            {

                while (true)
                {
                    //1초에 한번씩 Send
                    Thread.Sleep(1000);

                    //Send
                    gameSession_.Send_Login_REQ();

                    //Recv
                    if (gameSession_.Recv() == true)
                    {
                        Console.WriteLine("Recv Sucess");
                    }
                    else
                    {
                        Console.WriteLine("Recv Fail");
                    }
                }
            }
            else
            {
                Console.WriteLine("Connect Fail");
            }
        }
    }
}