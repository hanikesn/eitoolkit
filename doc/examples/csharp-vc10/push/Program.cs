using System;
using de.uni_stuttgart.eitoolkit;

namespace push
{
    class Program
    {
        static void Main(string[] args)
        {
            Description desc = new Description("Dummy 1", "dummy");
            desc.addDataSeries("val", new DataSeriesInfo(Value.Type.DOUBLE, 0, ""));

            int cnt = 0;

            using (Sender sender = new Sender(desc, new StringMap()))
            {
                DataMessage msg = sender.createDataMessage();

                long start = DateTime.Now.Ticks;
                while (DateTime.Now.Ticks < start + 5 * TimeSpan.TicksPerSecond)
                {
                    msg.setDouble("val", 42.0);
                    sender.sendMessage(msg);
                    cnt++;
                }
            }

            System.Console.Out.WriteLine(cnt);
            System.Console.ReadLine();
        }
    }
}
