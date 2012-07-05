using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using de.uni_stuttgart.eitoolkit;

namespace push
{
    class Program
    {
        static void Main(string[] args)
        {
            Sender sender = new Sender(new Description("csharp", "dummy"),  new StringMap());

            DataMessage msg = new DataMessage("csharp");

            int cnt = 0;

            long start = DateTime.Now.Ticks;
            while (DateTime.Now.Ticks < start + 5 * TimeSpan.TicksPerSecond)
            {
                sender.sendMessage(msg);
                cnt++;
            }
            System.Console.Out.WriteLine(cnt);
            System.Console.ReadLine();
        }
    }
}
