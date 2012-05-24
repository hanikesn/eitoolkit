#include <EIToolkit.h>

#include <iostream>
#include <ctime>

int main()
{
    std::cout << "push" << std::endl;

    std::map<std::string, std::string> options;

    EI::Sender sender(options);

    int start = clock();

    int cnt = 0;

    while(clock() < start + CLOCKS_PER_SEC*5)
    {
        EI::DataPacket p("simple_server");
        p.setString("msg",  "message");
        sender.sendPacket(p);
        cnt++;
    }
    std::cout << cnt << std::endl;
}
