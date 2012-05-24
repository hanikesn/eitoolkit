#include <EIToolkit.h>

#include <iostream>

int main()
{
    std::cout << "simple_server" << std::endl;

    std::map<std::string, std::string> options;

    EI::Sender sender(options);

    while(true)
    {
        std::string message;
        std::getline(std::cin, message);
        EI::DataPacket p("simple_server");
        p.setString("msg",  message);
        sender.sendPacket(p);
    }
}
