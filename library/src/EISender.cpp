#include "EISender.h"

namespace EI
{

class Sender::SenderImpl
{
public:
    SenderImpl(std::map<std::string, std::string> options);
    SenderImpl(std::map<std::string, std::string> options, Transport&, Presentation&);
    ~SenderImpl();

    void sendPacket(Packet);
};

Sender::Sender(std::map<std::string, std::string> options) :
    pimpl(new SenderImpl(options))
{}

Sender::Sender(std::map<std::string, std::string> options, Transport& transport, Presentation& presentation) :
    pimpl(new SenderImpl(options, transport, presentation))
{}

void Sender::sendPacket(Packet packet)
{
    pimpl->sendPacket(packet);
}

Sender::~Sender()
{
	delete pimpl;
}

}
