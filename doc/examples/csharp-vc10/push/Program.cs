using System;
using de.uni_stuttgart.eitoolkit;

namespace push
{
    class Program
    {
        static void Main(string[] args)
        {
            Description desc = new Description("C# Dummy", "dummy");
            desc.addDataSeries("val1", new DataSeriesInfo(Value.Type.STRING, 0, ""));
            desc.addDataSeries("val2", new DataSeriesInfo(Value.Type.DOUBLE, (int)DataSeriesInfo.Property.INTERPOLATABLE, ""));
            desc.addDataSeries("val3", new DataSeriesInfo(Value.Type.DOUBLE, (int)(DataSeriesInfo.Property.INTERPOLATABLE | DataSeriesInfo.Property.HAS_MINMAX), "", 0.0, 1.0));

            int cnt = 0;

            using (Sender sender = new Sender(desc, new StringMap()))
            {
                DataMessage msg = sender.createDataMessage();

                long start = DateTime.Now.Ticks;
                while (DateTime.Now.Ticks < start + 5 * TimeSpan.TicksPerSecond)
                {
                    msg.setString("val1", "hello");
                    msg.setDouble("val2", 42.0);
                    msg.setDouble("val3", 0.5);
                    sender.sendMessage(msg);
                    cnt++;
                }
            }

            System.Console.Out.WriteLine(cnt);
            System.Console.ReadLine();
        }
    }
}
