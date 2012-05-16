#include "EIReceiver.h"

namespace EI
{

class Receiver::ReceiverImpl
{
public:
    ReceiverImpl(std::map<std::string, std::string> options);
    ReceiverImpl(std::map<std::string, std::string> options, Transport&);
    ReceiverImpl(std::map<std::string, std::string> options, Transport&, Presentation&);
    ~ReceiverImpl();

    void sendDiscover();

    void addDataListener(DataObserver*);
    void removeDataListener(DataObserver*);

    void addControlListener(ControlObserver*);
    void removeControlListener(ControlObserver*);
};

Receiver::Receiver(std::map<std::string, std::string> options) :
    pimpl(new ReceiverImpl(options))
{}

Receiver::Receiver(std::map<std::string, std::string> options, Transport& transport) :
    pimpl(new ReceiverImpl(options, transport))
{}

Receiver::Receiver(std::map<std::string, std::string> options, Transport& transport, Presentation& presentation) :
    pimpl(new ReceiverImpl(options, transport, presentation))
{}

void Receiver::sendDiscover()
{
    pimpl->sendDiscover();
}

void Receiver::addDataListener(DataObserver * observer)
{
    pimpl->addDataListener(observer);
}

void Receiver::removeDataListener(DataObserver * observer)
{
    pimpl->removeDataListener(observer);
}

void Receiver::addControlListener(ControlObserver * observer)
{
    pimpl->addControlListener(observer);
}

void Receiver::removeControlListener(ControlObserver * observer)
{
    pimpl->removeControlListener(observer);
}

}
