#include <EIToolkit.h>

#include <iostream>

int main()
{
    std::cout << "simple_server" << std::endl;

    EI::StringMap options;

    EI::Description desc("asd");

    EI::Sender sender(desc, options);

    while(true)
    {
        std::string message;
        std::getline(std::cin, message);
        EI::DataMessage p("simple_server");
        p.setString("msg",  message);
        sender.sendMessage(p);
    }
}
