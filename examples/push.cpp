#include <EIToolkit.h>

#include <iostream>
#include <ctime>

int main()
{
    std::cout << "push" << std::endl;

    EI::StringMap options;

    EI::UDPTransport transport(options);
    EI::ProtobufPresentation presentation(options);

    EI::Sender sender(EI::Description("asd"), options, transport, presentation);

    int start = clock();

    int cnt = 0;

    const std::string msg1("msg");
    const std::string msg2("msg1");
    const std::string msg3("msg2");
    const std::string msg4("msg3");
    const std::string msg5("msg4");
    const std::string msg6("msg5");


    EI::DataMessage p("simple_server");
    while(clock() < start + CLOCKS_PER_SEC*5)
    {
        p.setString(msg1,  "message");
        p.setString(msg2,  "message");
        p.setString(msg3,  "message");
        p.setString(msg4,  "message");
        p.setString(msg5,  "message");
        p.setString(msg6,  "message");

        sender.sendMessage(p);
        cnt++;
    }
    std::cout << cnt << std::endl;
}
