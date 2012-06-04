#include "EIReceiver.h"

#include "EIDataMessage.h"
#include "EIJSONPresentation.h"
#include "EIUDPTransport.h"
#include "EIDiscoveryMessage.h"
#include "EIThread.h"
#include "helpers.h"

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
    ~ReceiverImpl();

    void discoverSenders();

    void addDataListener(DataListener&);
    void removeDataListener(DataListener&);

    void addCommunicationListener(CommunicationListener&);
    void removeCommunicationListener(CommunicationListener&);

    virtual void onPacket(Transport::Channel, ByteVector const&);

private:
    void init();
private:
    StringMap options;

	std::unique_ptr<Transport> own_transport;
	std::unique_ptr<Presentation> own_presentation;

	Transport& transport;
	Presentation& presentation;

    Thread::mutex mutex;
    std::vector<DataListener*> dataListeners;
    std::vector<CommunicationListener*> controlListeners;
};

Receiver::Receiver(StringMap const& options)
    : pimpl(new ReceiverImpl(options))
{}

Receiver::Receiver(StringMap const& options, Transport& transport)
    : pimpl(new ReceiverImpl(options, transport))
{}

Receiver::Receiver(StringMap const& options, Transport& transport, Presentation& presentation)
    : pimpl(new ReceiverImpl(options, transport, presentation))
{}

Receiver::~Receiver()
{
	delete pimpl;
}

void Receiver::discoverSenders()
{
    pimpl->discoverSenders();
}

void Receiver::addDataListener(DataListener& observer)
{
    pimpl->addDataListener(observer);
}

void Receiver::removeDataListener(DataListener& observer)
{
    pimpl->removeDataListener(observer);
}

void Receiver::addCommunicationListener(CommunicationListener& observer)
{
    pimpl->addCommunicationListener(observer);
}

void Receiver::removeCommunicationListener(CommunicationListener& observer)
{
    pimpl->removeCommunicationListener(observer);
}

Receiver::ReceiverImpl::ReceiverImpl(StringMap const& options)
    : options(options), own_transport(new UDPTransport(options)), own_presentation(new JSONPresentation(options)), transport(*own_transport), presentation(*own_presentation)
{
    init();
}

Receiver::ReceiverImpl::ReceiverImpl(StringMap const& options, Transport& transport)
    : options(options), own_presentation(new JSONPresentation(options)), transport(transport), presentation(*own_presentation)
{
    init();
}

Receiver::ReceiverImpl::ReceiverImpl(StringMap const& options, Transport& transport, Presentation& presentation)
	: options(options), transport(transport), presentation(presentation)
{
    init();
}

Receiver::ReceiverImpl::~ReceiverImpl()
{
    transport.removePacketListener(*this);
}

void Receiver::ReceiverImpl::init()
{
    transport.addPacketListener(Transport::ALL, *this);
}

void Receiver::ReceiverImpl::discoverSenders()
{
    ByteVector buffer;
    presentation.encode(DiscoveryMessage("Receiver"), buffer);
    transport.sendPacket(Transport::COMMUNICATION, buffer);
}

void Receiver::ReceiverImpl::addDataListener(DataListener& ob)
{
    Thread::lock_guard lock(mutex);
    dataListeners.push_back(&ob);
}

void Receiver::ReceiverImpl::removeDataListener(DataListener& ob)
{
    Thread::lock_guard lock(mutex);
    dataListeners.erase(std::remove(std::begin(dataListeners), std::end(dataListeners), &ob), std::end(dataListeners));
}

void Receiver::ReceiverImpl::addCommunicationListener(CommunicationListener& ob)
{
    Thread::lock_guard lock(mutex);
    controlListeners.push_back(&ob);
}

void Receiver::ReceiverImpl::removeCommunicationListener(CommunicationListener& ob)
{
    Thread::lock_guard lock(mutex);
    controlListeners.erase(std::remove(std::begin(controlListeners), std::end(controlListeners), &ob), std::end(controlListeners));
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
