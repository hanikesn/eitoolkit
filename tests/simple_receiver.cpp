#include <EIToolkit.h>

#include <iostream>
#include <algorithm>

class ExampleListener : public EI::DataListener
{
public:
    void onMessage(EI::DataMessage p) {
        std::cout << "Data: " << p.getSender() << " " << p.getMsgType() << std::endl;
        std::cout << "Msg: " << p.getString("msg") << std::endl;
    }
};

int main()
{
    std::cout << "simple_receiver" << std::endl;

    EI::StringMap options;

    EI::Receiver receiver(options);

    ExampleListener listener;
    receiver.addDataListener(&listener);

    std::cin.get();
}
