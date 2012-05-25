#include <EIToolkit.h>
#include <EIUDPTransport.h>
#include <EIJSONPresentation.h>

#include <iostream>

class DataListener : public EI::DataObserver
{
public:
    virtual ~DataListener() {}
    virtual void onPacket(EI::DataPacket const& p) {
        std::cout << "Data: " << p.getSender() << " " << p.getMsgtype() << std::endl;
    }

};

class ControlListener : public EI::ControlObserver
{
public:
    virtual ~ControlListener() {}
    virtual void onPacket(EI::Packet const& p) {
        std::cout << "Control: " << p.getSender() << " " << p.getMsgtype() << std::endl;
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
    EI::DataPacket data("Data");
    data.setDouble("asd", 5.0);
    data.setString("dfsdf", "Hallo Welt");
    server.sendPacket(data);

    std::cin.get();
}
