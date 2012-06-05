#include <EIToolkit.h>
#include <EIUDPTransport.h>
#include <EIJSONPresentation.h>

#include <iostream>
#include <algorithm>

class DataListener : public EI::DataListener
{
public:
    virtual ~DataListener() {}
    virtual void onMessage(EI::DataMessage p) {
        std::cout << "Data: " << p.getSender() << " " << p.getMsgType() << std::endl;
    }

};

class CommunicationListener : public EI::CommunicationListener
{
public:
    virtual ~CommunicationListener() {}
    virtual void onMessage(EI::Message const& p) {
        std::cout << "Communication: " << p.getSender() << " " << p.getMsgType() << std::endl;
        if(p.getMsgType()==EI::DescriptionMessage::IDENTIFIER) {
            EI::DescriptionMessage const& m = dynamic_cast<EI::DescriptionMessage const&>(p);
            auto const& d = m.getDescription();
            std::cout << "Device: " << d.getDeviceType() << std::endl;
            auto const & s = d.getDataSeries();
            std::for_each(s.begin(), s.end(), [](std::pair<const std::string, EI::DataSeriesInfo> v)
            {
                          std::cout << v.first << " " << v.second.getType() << std::endl;
            });
        }
    }

};

int main()
{
    EI::StringMap options;
    DataListener dataListener;
    CommunicationListener controlListener;

    EI::DiscoveryMessage msg = EI::DiscoveryMessage("asd");

    msg = EI::DiscoveryMessage("asd");

    EI::UDPTransport transport(options);
    EI::JSONPresentation presentation(options);
    EI::Description desc("test");
    desc.addDataSeries("x", EI::DataSeriesInfo(EI::Value::DOUBLE, EI::DataSeriesInfo::INTERPOLATABLE,"asd"));
    EI::Sender server(desc, options, transport, presentation);
    EI::Receiver receiver(options, transport);

    receiver.addDataListener(dataListener);
    receiver.addCommunicationListener(controlListener);
    receiver.discoverSenders();
    EI::DataMessage data("combined");
    data.setDouble("asd", 5.0);
    data.setString("dfsdf", "Hallo Welt");
    server.sendMessage(data);

    std::cin.get();
}
