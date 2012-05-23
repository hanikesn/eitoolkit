#include <EIToolkit.h>

#include <iostream>
#include <algorithm>

class DataListener : public EI::DataObserver
{
public:
    virtual void onPacket(EI::DataPacket const& p) {
        std::cout << "Data: " << p.getSender() << " " << p.getMsgtype() << std::endl;
        std::for_each(p.getStringValues().begin(), p.getStringValues().end(),
                     [](std::pair<std::string, std::string> const& pair)
        {
                      std::cout << pair.first << ": " << pair.second << std::endl;
        });
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
