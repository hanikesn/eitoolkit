#include <EIToolkit.h>

#include <iostream>

int main()
{
    std::map<std::string, std::string> options;

    EI::Sender sender(options);

    while(true)
    {
        sender.sendPacket(EI::DataPacket("Data"));
        std::cin.get();
    }
}
