using System;
using de.uni_stuttgart.eitoolkit;

namespace count
{
    class Program
    {
        static volatile int count = 0;

        class Listener : DataListener
        {
            public override void onMessage(DataMessage msg)
            {
                String str = msg.getSender();
                double val = msg.getDouble("val");
                count++;
            }
        }

        static void Main(string[] args)
        {
            DataListener listener = new Listener();

            using (Receiver receiver = new Receiver(new StringMap()))
            {
                receiver.addDataListener(listener);

                System.Console.ReadLine();
            }
            System.Console.WriteLine(count);
            System.Console.ReadLine();
        }
    }
}
