#include "EIReceiver.h"

#include "EIDataMessage.h"
#include "EIJSONPresentation.h"
#include "EIUDPTransport.h"
#include "EIDiscoveryMessage.h"
#include "EIThread.h"

#include <iostream>
#include <algorithm>

namespace EI
{

class Receiver::ReceiverImpl : public PacketObserver
{
public:
    ReceiverImpl(std::map<std::string, std::string> const& options);
    ReceiverImpl(std::map<std::string, std::string> const& options, Transport&);
    ReceiverImpl(std::map<std::string, std::string> const& options, Transport&, Presentation&);
    ~ReceiverImpl();

    void discoverSenders();

    void addDataListener(DataObserver&);
    void removeDataListener(DataObserver&);

    void addControlListener(ControlObserver&);
    void removeControlListener(ControlObserver&);

    virtual void onPacket(Transport::Type, std::vector<Byte> const&);

private:
    void init();
private:
    std::map<std::string, std::string> options;

	std::unique_ptr<Transport> own_transport;
	std::unique_ptr<Presentation> own_presentation;

	Transport& transport;
	Presentation& presentation;

    Thread::mutex mutex;
    std::vector<DataObserver*> dataObservers;
    std::vector<ControlObserver*> controlObservers;

    std::vector<Byte> buffer;
};

Receiver::Receiver(std::map<std::string, std::string> const& options)
    : pimpl(new ReceiverImpl(options))
{}

Receiver::Receiver(std::map<std::string, std::string> const& options, Transport& transport)
    : pimpl(new ReceiverImpl(options, transport))
{}

Receiver::Receiver(std::map<std::string, std::string> const& options, Transport& transport, Presentation& presentation)
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

void Receiver::addDataListener(DataObserver& observer)
{
    pimpl->addDataListener(observer);
}

void Receiver::removeDataListener(DataObserver& observer)
{
    pimpl->removeDataListener(observer);
}

void Receiver::addControlListener(ControlObserver& observer)
{
    pimpl->addControlListener(observer);
}

void Receiver::removeControlListener(ControlObserver& observer)
{
    pimpl->removeControlListener(observer);
}

Receiver::ReceiverImpl::ReceiverImpl(std::map<std::string, std::string> const& options)
    : options(options), own_transport(new UDPTransport(options)), own_presentation(new JSONPresentation(options)), transport(*own_transport), presentation(*own_presentation)
{
    init();
}

Receiver::ReceiverImpl::ReceiverImpl(std::map<std::string, std::string> const& options, Transport& transport)
    : options(options), own_presentation(new JSONPresentation(options)), transport(transport), presentation(*own_presentation)
{
    init();
}

Receiver::ReceiverImpl::ReceiverImpl(std::map<std::string, std::string> const& options, Transport& transport, Presentation& presentation)
	: options(options), transport(transport), presentation(presentation)
{
    init();
}

Receiver::ReceiverImpl::~ReceiverImpl()
{
    transport.removePacketObserver(*this);
}

void Receiver::ReceiverImpl::init()
{
    transport.addPacketObserver(Transport::ALL, *this);
}

void Receiver::ReceiverImpl::discoverSenders()
{
    presentation.encode(DiscoveryMessage("Receiver"), buffer);
    transport.sendPacket(Transport::CONTROL, buffer);
}

void Receiver::ReceiverImpl::addDataListener(DataObserver& ob)
{
    Thread::lock_guard lock(mutex);
    dataObservers.push_back(&ob);
}

void Receiver::ReceiverImpl::removeDataListener(DataObserver& ob)
{
    Thread::lock_guard lock(mutex);
    dataObservers.erase(std::remove(std::begin(dataObservers), std::end(dataObservers), &ob), std::end(dataObservers));
}

void Receiver::ReceiverImpl::addControlListener(ControlObserver& ob)
{
    Thread::lock_guard lock(mutex);
    controlObservers.push_back(&ob);
}

void Receiver::ReceiverImpl::removeControlListener(ControlObserver& ob)
{
    Thread::lock_guard lock(mutex);
    controlObservers.erase(std::remove(std::begin(controlObservers), std::end(controlObservers), &ob), std::end(controlObservers));
}

void Receiver::ReceiverImpl::onPacket(Transport::Type type, std::vector<Byte> const& data)
{
    std::shared_ptr<Message> p;
    try {
        p = presentation.decode(std::move(data));
    } catch(std::exception& e) {
        std::cerr << "Error: Invalid packet: " << e.what();
        return;
    }

    Thread::lock_guard lock(mutex);
    switch(type) {
    case Transport::DATA:
        std::for_each(std::begin(dataObservers), std::end(dataObservers),
        [&p](DataObserver* ob)
        {
            std::shared_ptr<DataMessage> dp = std::dynamic_pointer_cast<DataMessage>(p);
            if(dp)
                ob->onMessage(std::move(*dp));
        });
        break;
    case Transport::CONTROL:
        std::for_each(std::begin(controlObservers), std::end(controlObservers),
        [&p](ControlObserver* ob)
        {
            ob->onMessage(std::move(*p));
        });
        break;
    default:
        break;
    }
}

}
