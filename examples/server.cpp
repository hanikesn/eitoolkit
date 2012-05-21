#include <EIToolkit.h>
#include <EIUDPTransport.h>
#include <EIJSONPresentation.h>

#include <iostream>

class Listener : public EI::DataObserver
{
public:
    virtual ~Listener() {};
    virtual void onPacket(EI::Packet p) {
        std::cout << &p << std::endl;
    }

};

int main()
{
    std::map<std::string, std::string> options = {{"name","Test"}};
    EI::UDPTransport transport(options);
    EI::JSONPresentation presentation(options);
    EI::Sender server(options, transport, presentation);
    EI::Receiver receiver(options, transport);

    Listener listener;

    receiver.addDataListener(&listener);
    server.sendPacket(EI::Packet());

    while(true);
}
