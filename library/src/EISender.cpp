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
    ~SenderImpl();

    void sendMessage(Message const&);

    void onPacket(Transport::Channel, ByteVector const&);

private:
    StringMap options;

	std::unique_ptr<UDPTransport> own_transport;
	std::unique_ptr<Presentation> own_presentation;

	Transport& transport;
	Presentation& presentation;

    Description description;

    ByteVector buffer;
};

Sender::Sender(Description const& description, StringMap const& options)
    : pimpl(new SenderImpl(description, options))
{}

Sender::Sender(Description const& description, StringMap const& options, Transport& transport, Presentation& presentation)
    : pimpl(new SenderImpl(description, options, transport, presentation))
{}

void Sender::sendMessage(Message const& packet)
{
    pimpl->sendMessage(packet);
}

Sender::~Sender()
{
	delete pimpl;
}

Sender::SenderImpl::SenderImpl(Description const& description, StringMap const& options)
    : options(options), own_transport(new UDPTransport(options)), own_presentation(new JSONPresentation(options)), transport(*own_transport), presentation(*own_presentation), description(description)
{}

Sender::SenderImpl::SenderImpl(Description const& description, StringMap const& options, Transport& transport, Presentation& presentation)
    : options(options), transport(transport), presentation(presentation), description(description)
{
    transport.addPacketListener(Transport::COMMUNICATION, *this);
}

Sender::SenderImpl::~SenderImpl()
{
    transport.removePacketListener(*this);
}

void Sender::SenderImpl::sendMessage(Message const& packet)
{
    presentation.encode(packet, buffer);
    transport.sendPacket(packet.getMsgType() == DataMessage::IDENTIFIER ? Transport::DATA :  Transport::COMMUNICATION, buffer);
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
