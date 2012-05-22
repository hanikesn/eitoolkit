#include <EIToolkit.h>
#include <EIUDPTransport.h>
#include <EIJSONPresentation.h>

#include <iostream>

class DataListener : public EI::DataObserver
{
public:
    virtual ~DataListener() {}
    virtual void onPacket(EI::DataPacket const& p) {
        std::cout << "Data: " << &p << std::endl;
    }

};

class ControlListener : public EI::ControlObserver
{
public:
    virtual ~ControlListener() {}
    virtual void onPacket(EI::Packet const& p) {
        std::cout << "Control: " << &p << std::endl;
    }

};

int main()
{
    std::map<std::string, std::string> options = {{"name","Test"}};
    DataListener dataListener;
    ControlListener controlListener;

    EI::UDPTransport transport(options);
    EI::JSONPresentation presentation(options);
    EI::Sender server(options, transport, presentation);
    EI::Receiver receiver(options, transport);

    receiver.addDataListener(dataListener);
    receiver.addControlListener(controlListener);
    server.sendPacket(EI::Packet("Discover", "discover"));
    server.sendPacket(EI::DataPacket("Data"));

    while(true);
}
