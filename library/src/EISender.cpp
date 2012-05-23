#include "EISender.h"
#include "EIUDPTransport.h"
#include "EIJSONPresentation.h"

#include <memory>

namespace EI
{

class Sender::SenderImpl
{
public:
    SenderImpl(std::map<std::string, std::string> const& options);
    SenderImpl(std::map<std::string, std::string> const& options, Transport&, Presentation&);
    ~SenderImpl();

    void sendPacket(Packet const&);

private:
    std::map<std::string, std::string> options;

	std::unique_ptr<UDPTransport> own_transport;
	std::unique_ptr<Presentation> own_presentation;

	Transport& transport;
	Presentation& presentation;
};

Sender::Sender(std::map<std::string, std::string> const& options)
    : pimpl(new SenderImpl(options))
{}

Sender::Sender(std::map<std::string, std::string> const& options, Transport& transport, Presentation& presentation)
	: pimpl(new SenderImpl(options, transport, presentation))
{}

void Sender::sendPacket(Packet const& packet)
{
    pimpl->sendPacket(packet);
}

Sender::~Sender()
{
	delete pimpl;
}

Sender::SenderImpl::SenderImpl(std::map<std::string, std::string> const& options)
    : options(options), own_transport(new UDPTransport(options)), own_presentation(new JSONPresentation(options)),  transport(*own_transport), presentation(*own_presentation)
{}

Sender::SenderImpl::SenderImpl(std::map<std::string, std::string> const& options, Transport& transport, Presentation& presentation)
	: options(options), transport(transport), presentation(presentation)
{}

Sender::SenderImpl::~SenderImpl()
{}

void Sender::SenderImpl::sendPacket(Packet const& packet)
{
    transport.sendBytePacket(packet.getMsgtype() == "data" ? Transport::DATA :  Transport::CONTROL, presentation.encode(packet));
}

}
