#include "EISender.h"
#include "EIUDPTransport.h"

#include <memory>

namespace EI
{

class Sender::SenderImpl
{
public:
    SenderImpl(std::map<std::string, std::string> options);
    SenderImpl(std::map<std::string, std::string> options, Transport&, Presentation&);
    ~SenderImpl();

    void sendPacket(Packet);

private:
	std::unique_ptr<UDPTransport> own_transport;
	std::unique_ptr<Presentation> own_presentation;

	Transport& transport;
	Presentation& presentation;

	std::map<std::string, std::string> options;
};

Sender::Sender(std::map<std::string, std::string> options)
    : pimpl(new SenderImpl(options))
{}

Sender::Sender(std::map<std::string, std::string> options, Transport& transport, Presentation& presentation)
	: pimpl(new SenderImpl(options, transport, presentation))
{}

void Sender::sendPacket(Packet packet)
{
    pimpl->sendPacket(packet);
}

Sender::~Sender()
{
	delete pimpl;
}

Sender::SenderImpl::SenderImpl(std::map<std::string, std::string> options)
	: options(options), own_transport(new UDPTransport(options)), transport(*own_transport), presentation(*own_presentation)
{}

Sender::SenderImpl::SenderImpl(std::map<std::string, std::string> options, Transport& transport, Presentation& presentation)
	: options(options), transport(transport), presentation(presentation)
{}

Sender::SenderImpl::~SenderImpl()
{}

void Sender::SenderImpl::sendPacket(Packet packet)
{
	transport.sendBytePacket(Transport::DATA, presentation.encode(packet));
}

}
