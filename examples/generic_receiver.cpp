#include <EIToolkit.h>

#include <iostream>
#include <algorithm>

class ExampleListener : public EI::DataObserver
{
public:
    void onMessage(EI::DataMessage const& p) {
        std::cout << "Data: " << p.getSender() << " " << p.getMsgtype() << std::endl;
        std::for_each(p.getValues().begin(), p.getValues().end(),
                      [](std::pair<const std::string, EI::Value> const& pair)
        {
                      std::cout << pair.first << " " << pair.second << std::endl;
        });
    }
};

int main()
{
    std::cout << "generic_receiver" << std::endl;

    std::map<std::string, std::string> options;

    EI::Receiver receiver(options);

    ExampleListener listener;
    receiver.addDataListener(listener);

    std::cin.get();
}

