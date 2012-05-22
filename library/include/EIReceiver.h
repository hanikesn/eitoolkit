#ifndef EIReceiver_H__
#define EIReceiver_H__

#include "EIPrerequisites.h"
#include "EITransport.h"
#include "EIPresentation.h"
#include "EIDataPacket.h"

#include <map>
#include <string>

namespace EI
{

class EITOOLKIT_EXPORT DataObserver
{
public:
    virtual ~DataObserver() {}
    virtual void onPacket(DataPacket const&) = 0;
};

class EITOOLKIT_EXPORT ControlObserver
{
public:
    virtual ~ControlObserver() {}
    virtual void onPacket(Packet const&) = 0;
};

class EITOOLKIT_EXPORT Receiver
{
public:
    Receiver(std::map<std::string, std::string> const& options);
    Receiver(std::map<std::string, std::string> const& options, Transport&);
    Receiver(std::map<std::string, std::string> const& options, Transport&, Presentation&);
    ~Receiver();

    void sendDiscover();

    void addDataListener(DataObserver&);
    void removeDataListener(DataObserver&);

    void addControlListener(ControlObserver&);
    void removeControlListener(ControlObserver&);
private:
    // Disable copying
    Receiver(const Receiver &);
    Receiver &operator=(const Receiver &);
private:
    class ReceiverImpl;
    ReceiverImpl* const pimpl;
};

}

#endif
