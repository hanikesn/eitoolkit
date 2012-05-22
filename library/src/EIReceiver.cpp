#include "EIReceiver.h"

#include "EIJSONPresentation.h"
#include "EIUDPTransport.h"

#include <boost/thread/mutex.hpp>

namespace EI
{

class Receiver::ReceiverImpl : public BytePacketObserver
{
public:
    ReceiverImpl(std::map<std::string, std::string> const& options);
    ReceiverImpl(std::map<std::string, std::string> const& options, Transport&);
    ReceiverImpl(std::map<std::string, std::string> const& options, Transport&, Presentation&);
    ~ReceiverImpl();

    void sendDiscover();

    void addDataListener(DataObserver&);
    void removeDataListener(DataObserver&);

    void addControlListener(ControlObserver&);
    void removeControlListener(ControlObserver&);

    virtual void onBytePacket(Transport::Type, std::vector<Byte> const&);

private:
    void init();
private:
    std::map<std::string, std::string> options;

	std::unique_ptr<Transport> own_transport;
	std::unique_ptr<Presentation> own_presentation;

	Transport& transport;
	Presentation& presentation;

    boost::mutex mutex;
    std::vector<DataObserver*> dataObservers;
    std::vector<ControlObserver*> controlObservers;
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

void Receiver::sendDiscover()
{
    pimpl->sendDiscover();
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
    transport.removeBytePacketObserver(*this);
}

void Receiver::ReceiverImpl::init()
{
    transport.addBytePacketObserver(Transport::ALL, *this);
}

void Receiver::ReceiverImpl::sendDiscover()
{
    transport.sendBytePacket(Transport::CONTROL, presentation.encode(Packet("name", "discover")));
}

void Receiver::ReceiverImpl::addDataListener(DataObserver& ob)
{
    boost::lock_guard<boost::mutex> lock(mutex);
    dataObservers.push_back(&ob);
}

void Receiver::ReceiverImpl::removeDataListener(DataObserver& ob)
{
    boost::lock_guard<boost::mutex> lock(mutex);
    std::remove(std::begin(dataObservers), std::end(dataObservers), &ob);
}

void Receiver::ReceiverImpl::addControlListener(ControlObserver& ob)
{
    boost::lock_guard<boost::mutex> lock(mutex);
    controlObservers.push_back(&ob);
}

void Receiver::ReceiverImpl::removeControlListener(ControlObserver& ob)
{
    boost::lock_guard<boost::mutex> lock(mutex);
    std::remove(std::begin(controlObservers), std::end(controlObservers), &ob);
}

void Receiver::ReceiverImpl::onBytePacket(Transport::Type type, std::vector<Byte> const& data)
{
    std::shared_ptr<Packet> p = presentation.decode(std::move(data));
    boost::lock_guard<boost::mutex> lock(mutex);    
    switch(type) {
    case Transport::DATA:
        std::for_each(std::begin(dataObservers), std::end(dataObservers),
        [&p](DataObserver* ob)
        {
            std::shared_ptr<DataPacket> dp = std::dynamic_pointer_cast<DataPacket>(p);
            if(dp)
                ob->onPacket(std::move(*dp));
        });
        break;
    case Transport::CONTROL:
        std::for_each(std::begin(controlObservers), std::end(controlObservers),
        [&p](ControlObserver* ob)
        {
            ob->onPacket(std::move(*p));
        });
        break;
    default:
        break;
    }
}

}
