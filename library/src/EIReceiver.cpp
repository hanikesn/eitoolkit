#include "EIReceiver.h"

#include "EIDataMessage.h"
#include "EIJSONPresentation.h"
#include "EIUDPTransport.h"
#include "EIDiscoveryMessage.h"
#include "EIThread.h"
#include "helpers.h"
#include "PresentationManager.h"

#include <iostream>
#include <algorithm>

namespace EI
{

DataListener::~DataListener() {}

CommunicationListener::~CommunicationListener() {}

class Receiver::ReceiverImpl : public PacketListener
{
public:
    ReceiverImpl(StringMap const& options);
    ReceiverImpl(StringMap const& options, Transport&);
    ReceiverImpl(StringMap const& options, Transport&, Presentation&);

    void init();

    virtual void onPacket(Transport::Channel, ByteVector const&);

    StringMap options;

	std::unique_ptr<Transport> own_transport;

	Transport& transport;
    PresentationManager presentation;

    Thread::mutex mutex;
    std::vector<DataListener*> dataListeners;
    std::vector<CommunicationListener*> controlListeners;
};

Receiver::Receiver(StringMap const& options)
    : pimpl(new ReceiverImpl(options))
{
    pimpl->init();
}

Receiver::Receiver(StringMap const& options, Transport& transport)
    : pimpl(new ReceiverImpl(options, transport))
{
    pimpl->init();
}

Receiver::Receiver(StringMap const& options, Transport& transport, Presentation& presentation)
    : pimpl(new ReceiverImpl(options, transport, presentation))
{
    pimpl->init();
}

Receiver::~Receiver()
{
    pimpl->transport.removePacketListener(pimpl);
	delete pimpl;
}

Receiver::ReceiverImpl::ReceiverImpl(StringMap const& options)
    : options(options), own_transport(new UDPTransport(options)), transport(*own_transport), presentation(options, 0)
{
}

Receiver::ReceiverImpl::ReceiverImpl(StringMap const& options, Transport& transport)
    : options(options), transport(transport), presentation(options, 0)
{
}

Receiver::ReceiverImpl::ReceiverImpl(StringMap const& options, Transport& transport, Presentation& presentation)
    : options(options), transport(transport), presentation(options, &presentation)
{
}

void Receiver::ReceiverImpl::init()
{
    transport.addPacketListener(Transport::ALL, this);
}

void Receiver::discoverSenders()
{
    ByteVector buffer;
    pimpl->presentation.encode(DiscoveryMessage("Receiver"), buffer);
    try {
        pimpl->transport.sendPacket(Transport::COMMUNICATION, buffer);
    } catch (EI::Exception const& e) {
        std::cerr << e.what() << "\n";
    }
}

void Receiver::addDataListener(DataListener* ob)
{
    if(!ob)
        return;
    Thread::lock_guard lock(pimpl->mutex);
    pimpl->dataListeners.push_back(ob);
}

void Receiver::removeDataListener(DataListener *ob)
{
    Thread::lock_guard lock(pimpl->mutex);
    pimpl->dataListeners.erase(std::remove(pimpl->dataListeners.begin(), pimpl->dataListeners.end(), ob), pimpl->dataListeners.end());
}

void Receiver::addCommunicationListener(CommunicationListener* ob)
{
    if(!ob)
        return;
    Thread::lock_guard lock(pimpl->mutex);
    pimpl->controlListeners.push_back(ob);
}

void Receiver::removeCommunicationListener(CommunicationListener* ob)
{
    Thread::lock_guard lock(pimpl->mutex);
    pimpl->controlListeners.erase(std::remove(pimpl->controlListeners.begin(), pimpl->controlListeners.end(), ob), pimpl->controlListeners.end());
}

void Receiver::ReceiverImpl::onPacket(Transport::Channel type, ByteVector const& data)
{
    std::unique_ptr<Message> p;
    try {
        p = presentation.decode(data);
    } catch(std::exception& e) {
        std::cerr << "Error: Invalid packet: " << e.what();
        return;
    }

    Thread::lock_guard lock(mutex);
    switch(type)
    {
    case Transport::DATA:
    {
        std::unique_ptr<DataMessage> dp = unique_dynamic_cast<DataMessage>(p);
        if(!dp)
            break;
        std::for_each(std::begin(dataListeners), std::end(dataListeners),
        [&dp](DataListener* ob)
        {
            ob->onMessage(*dp);
        });
    }
        break;
    case Transport::COMMUNICATION:
        std::for_each(std::begin(controlListeners), std::end(controlListeners),
        [&p](CommunicationListener* ob)
        {
            ob->onMessage(*p);
        });
        break;
    default:
        break;
    }
}

}
