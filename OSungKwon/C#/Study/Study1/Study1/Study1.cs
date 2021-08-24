using System;
using static System.Console;

namespace Study1
{
    class Study1
    {
        static void Main(string[] args)
        {
            if(args.Length == 0)
            {
                Console.WriteLine(" 사용법 : HelloWorld.exe <Osung>");
                return;
            }

            WriteLine("Hello, {0}!", args[0]);
        }

    }
}
