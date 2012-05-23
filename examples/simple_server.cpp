#include <EIToolkit.h>

#include <iostream>

int main()
{
    std::map<std::string, std::string> options;

    EI::Sender sender(options);

    while(true)
    {
        EI::DataPacket p("simple_server");
        p.setString("x", "24");
        p.setString("y", "35");
        sender.sendPacket(p);
        std::cin.get();
    }
}
