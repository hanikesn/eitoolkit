#include <EIToolkit.h>

#include <iostream>
#include <ctime>
#include <boost/chrono.hpp>

typedef boost::chrono::high_resolution_clock Clock;

int main()
{
    std::cout << "benchmark" << std::endl;

    EI::StringMap options;

    EI::UDPTransport transport(options);
    EI::JSONPresentation presentation(options);
    EI::Sender sender(EI::Description("asd", "asd"), options, transport, presentation);

    const std::string id = "val";

    int cnt = 0;

    EI::DataMessage msg = sender.createDataMessage();

    while(true)
    {
        {
            EI::BlockingReceiver rec(options, transport, presentation);
            bool waiting = true;
            while(waiting)
            {
                rec.waitForMessages(10000);
                std::vector<EI::DataMessage> msgs = rec.getMessages();
                std::for_each(msgs.begin(), msgs.end(), 
                    [&waiting](const EI::DataMessage& msg)
                    {
                        if(msg.getSender() == "count")
                        {
                            waiting = false;
                        }
                    }
                );
            }
        }
        Clock::time_point start = Clock::now();
        while(Clock::now() < start + boost::chrono::seconds(5))
        {
            msg.setDouble(id,  100.0);
 
            sender.sendMessage(msg);
            cnt++;
        }
        std::cout << cnt << std::endl;
    }
}
