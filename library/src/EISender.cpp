#include "EISender.h"
#include "EIUDPTransport.h"
#include "EIJSONPresentation.h"
#include "EIDescription.h"
#include "EIDescriptionMessage.h"
#include "EIDiscoveryMessage.h"
#include "EIDataMessage.h"

#include <memory>

namespace EI
{

class Sender::SenderImpl : public EI::PacketListener
{
public:
    SenderImpl(Description const&, StringMap const& options);
    SenderImpl(Description const&, StringMap const& options, Transport&, Presentation&);

    void onPacket(Transport::Channel, ByteVector const&);

    StringMap options;

	std::unique_ptr<UDPTransport> own_transport;
	std::unique_ptr<Presentation> own_presentation;

	Transport& transport;
	Presentation& presentation;

    Description description;
};

Sender::Sender(Description const& description, StringMap const& options)
    : pimpl(new SenderImpl(description, options))
{
    pimpl->transport.addPacketListener(Transport::COMMUNICATION, pimpl);
}

Sender::Sender(Description const& description, StringMap const& options, Transport& transport, Presentation& presentation)
    : pimpl(new SenderImpl(description, options, transport, presentation))
{
    pimpl->transport.addPacketListener(Transport::COMMUNICATION, pimpl);
}

Sender::~Sender()
{
    pimpl->transport.removePacketListener(pimpl);
	delete pimpl;
}

Sender::SenderImpl::SenderImpl(Description const& description, StringMap const& options)
    : options(options), own_transport(new UDPTransport(options)), own_presentation(new JSONPresentation(options)), transport(*own_transport), presentation(*own_presentation), description(description)
{

}

Sender::SenderImpl::SenderImpl(Description const& description, StringMap const& options, Transport& transport, Presentation& presentation)
    : options(options), transport(transport), presentation(presentation), description(description)
{
}

void Sender::sendMessage(Message const& packet)
{
    ByteVector buffer;
    pimpl->presentation.encode(packet, buffer);
    pimpl->transport.sendPacket(packet.getMsgType() == DataMessage::IDENTIFIER ? Transport::DATA :  Transport::COMMUNICATION, buffer);
}

void Sender::SenderImpl::onPacket(Transport::Channel type, ByteVector const& bytes)
{
    if(type != Transport::COMMUNICATION)
        return;

    auto p = presentation.decode(bytes);

    if(p->getMsgType() == DiscoveryMessage::IDENTIFIER) {
        ByteVector buffer;
        presentation.encode(DescriptionMessage("Sender", description), buffer);
        transport.sendPacket(Transport::COMMUNICATION, buffer);
    }
}

}
