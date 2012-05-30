#include <EIToolkit.h>

#include <iostream>
#include <ctime>

int main()
{
    std::cout << "push" << std::endl;

    std::map<std::string, std::string> options;

    EI::Sender sender(EI::Description("asd"), options);

    int start = clock();

    int cnt = 0;

    const std::string msg("msg");
    const std::string message("message");

    EI::DataPacket p("simple_server");
    while(clock() < start + CLOCKS_PER_SEC*5)
    {
        p.setString(msg,  message);
        sender.sendPacket(p);
        cnt++;
    }
    std::cout << cnt << std::endl;
}
