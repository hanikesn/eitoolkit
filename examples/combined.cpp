#include <EIToolkit.h>
#include <EIUDPTransport.h>
#include <EIJSONPresentation.h>

#include <iostream>

class DataListener : public EI::DataObserver
{
public:
    virtual ~DataListener() {}
    virtual void onPacket(EI::DataPacket const& p) {
        std::cout << "Data: " << p.getName() << " " << p.getType() << std::endl;
    }

};

class ControlListener : public EI::ControlObserver
{
public:
    virtual ~ControlListener() {}
    virtual void onPacket(EI::Packet const& p) {
        std::cout << "Control: " << p.getName() << " " << p.getType() << std::endl;
    }

};

int main()
{
    std::map<std::string, std::string> options;
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

    std::cin.get();

    std::cout << "end" << std::endl;
}
