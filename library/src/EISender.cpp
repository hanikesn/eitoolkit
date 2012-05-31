#include "EISender.h"
#include "EIUDPTransport.h"
#include "EIJSONPresentation.h"
#include "EIDescription.h"
#include "EIDescriptionPacket.h"
#include "EIDiscoverPacket.h"
#include "EIDataPacket.h"

#include <memory>

namespace EI
{

class Sender::SenderImpl : public EI::BytePacketObserver
{
public:
    SenderImpl(Description const&, std::map<std::string, std::string> const& options);
    SenderImpl(Description const&, std::map<std::string, std::string> const& options, Transport&, Presentation&);
    ~SenderImpl();

    void sendPacket(Packet const&);

    void onBytePacket(Transport::Type, std::vector<Byte> const&);

private:
    std::map<std::string, std::string> options;

	std::unique_ptr<UDPTransport> own_transport;
	std::unique_ptr<Presentation> own_presentation;

	Transport& transport;
	Presentation& presentation;

    Description description;

    std::vector<Byte> buffer;
};

Sender::Sender(Description const& description, std::map<std::string, std::string> const& options)
    : pimpl(new SenderImpl(description, options))
{}

Sender::Sender(Description const& description, std::map<std::string, std::string> const& options, Transport& transport, Presentation& presentation)
    : pimpl(new SenderImpl(description, options, transport, presentation))
{}

void Sender::sendPacket(Packet const& packet)
{
    pimpl->sendPacket(packet);
}

Sender::~Sender()
{
	delete pimpl;
}

Sender::SenderImpl::SenderImpl(Description const& description, std::map<std::string, std::string> const& options)
    : options(options), own_transport(new UDPTransport(options)), own_presentation(new JSONPresentation(options)), transport(*own_transport), presentation(*own_presentation), description(description)
{}

Sender::SenderImpl::SenderImpl(Description const& description, std::map<std::string, std::string> const& options, Transport& transport, Presentation& presentation)
    : options(options), transport(transport), presentation(presentation), description(description)
{
    transport.addBytePacketObserver(Transport::CONTROL, *this);
}

Sender::SenderImpl::~SenderImpl()
{
    transport.removeBytePacketObserver(*this);
}

void Sender::SenderImpl::sendPacket(Packet const& packet)
{
    presentation.encode(packet, buffer);
    transport.sendBytePacket(packet.getMsgtype() == DataMessage::IDENTIFIER ? Transport::DATA :  Transport::CONTROL, buffer);
}

void Sender::SenderImpl::onBytePacket(Transport::Type type, std::vector<Byte> const& bytes)
{
    if(type != Transport::CONTROL)
        return;

    auto p = presentation.decode(bytes);

    if(p->getMsgtype() == DiscoverPacket::IDENTIFIER) {
        std::vector<Byte> buffer;
        presentation.encode(DescriptionPacket("Sender", description), buffer);
        transport.sendBytePacket(Transport::CONTROL, buffer);
    }
}

}
