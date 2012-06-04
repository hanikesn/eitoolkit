#include <EIToolkit.h>

#include <iostream>
#include <algorithm>

class ExampleListener : public EI::DataListener
{
public:
    void onMessage(EI::DataMessage p) {
        std::cout << "Data: " << p.getSender() << " " << p.getMsgType() << std::endl;
        auto c = p.getContent();
        std::for_each(c.begin(), c.end(),
                      [](std::pair<const std::string, EI::Value> const& pair)
        {
                      std::cout << pair.first << " " << pair.second << std::endl;
        });
    }
};

int main()
{
    std::cout << "generic_receiver" << std::endl;

    EI::StringMap options;

    EI::Receiver receiver(options);

    ExampleListener listener;
    receiver.addDataListener(listener);

    std::cin.get();
}

