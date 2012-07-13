#include <EIToolkit.h>

#include <iostream>
#include <algorithm>

#include <boost/chrono.hpp>
#include <boost/thread.hpp>

volatile int count = 0;

class ExampleListener : public EI::DataListener
{
public:
    void onMessage(EI::DataMessage p) {
       std::string test =  p.getString("msg");
       count++;
    }
};

int main()
{
    std::cout << "count" << std::endl;

    EI::StringMap options;

    EI::UDPTransport transport(options);
    EI::JSONPresentation presentation(options);
    EI::Receiver receiver(options, transport, presentation);

    ExampleListener listener;
    receiver.addDataListener(&listener);

    {
        EI::Sender sender(EI::Description("count", "dummy"), options, transport, presentation);
        EI::DataMessage msg = sender.createDataMessage();
        msg.setDouble("seconds", 15);
        sender.sendMessage(msg);
        boost::this_thread::sleep(boost::posix_time::milliseconds(250));
    }

    std::cin.get();

    std::cerr << count << "\n";
}
