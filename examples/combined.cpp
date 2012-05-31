#include <EIToolkit.h>
#include <EIUDPTransport.h>
#include <EIJSONPresentation.h>

#include <iostream>

class DataListener : public EI::DataListener
{
public:
    virtual ~DataListener() {}
    virtual void onMessage(EI::DataMessage const& p) {
        std::cout << "Data: " << p.getSender() << " " << p.getMsgType() << std::endl;
    }

};

class ControlListener : public EI::ControlListener
{
public:
    virtual ~ControlListener() {}
    virtual void onMessage(EI::Message const& p) {
        std::cout << "Control: " << p.getSender() << " " << p.getMsgType() << std::endl;
    }

};

int main()
{
    std::map<std::string, std::string> options;
    DataListener dataListener;
    ControlListener controlListener;

    EI::UDPTransport transport(options);
    EI::JSONPresentation presentation(options);
    EI::Sender server(EI::Description("test"), options, transport, presentation);
    EI::Receiver receiver(options, transport);

    receiver.addDataListener(dataListener);
    receiver.addControlListener(controlListener);
    server.sendMessage(EI::DiscoveryMessage("combined"));
    EI::DataMessage data("combined");
    data.setDouble("asd", 5.0);
    data.setString("dfsdf", "Hallo Welt");
    server.sendMessage(data);

    std::cin.get();
}
