using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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
                count++;
            }
        }

        static void Main(string[] args)
        {
            DataListener listener = new Listener();
            Receiver receiver = new Receiver(new StringMap());
            receiver.addDataListener(listener);

            System.Console.ReadLine();
            System.Console.WriteLine(count);
            System.Console.ReadLine();
        }
    }
}
