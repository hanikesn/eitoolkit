#include <EIToolkit.h>

#include <iostream>
#include <algorithm>

class ExampleListener : public EI::DataObserver
{
public:
    void onPacket(EI::DataPacket const& p) {
        std::cout << "Data: " << p.getSender() << " " << p.getMsgtype() << std::endl;
        std::cout << "Msg: " << p.getString("msg") << std::endl;
    }
};

int main()
{
    std::cout << "simple_receiver" << std::endl;

    std::map<std::string, std::string> options;
    options["UDPPort"] = "31337";

    EI::Receiver receiver(options);

    ExampleListener listener;
    receiver.addDataListener(listener);

    std::cin.get();
}
