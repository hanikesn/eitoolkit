#include <EIToolkit.h>

#include <iostream>

class DataListener : public EI::DataObserver
{
public:
    virtual void onPacket(EI::DataPacket const& p) {
        std::cout << "Data: " << p.getSender() << " " << p.getMsgtype() << std::endl;
    }

};

int main()
{
    std::map<std::string, std::string> options;
    DataListener dataListener;

    EI::Receiver receiver(options);

    receiver.addDataListener(dataListener);

    std::cin.get();
}
