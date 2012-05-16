#ifndef EIReceiver_H__
#define EIReceiver_H__

#include "EIPrerequisites.h"
#include "EITransport.h"
#include "EIPresentation.h"

#include <map>
#include <memory>
#include <string>

namespace EI
{

class EITOOLKIT_EXPORT DataObserver
{
public:
    virtual ~DataObserver() {};
    virtual void onPacket(Packet) = 0;
};

class EITOOLKIT_EXPORT ControlObserver
{
public:
    virtual ~ControlObserver() {};
    virtual void onPacket(Packet) = 0;
};

class EITOOLKIT_EXPORT Receiver
{
public:
    /// Erstellt einen UPD Sender mit JSON Darstellung
    /// Options: z.B. Name = asd etc.
    Receiver(std::map<std::string, std::string> options);
    Receiver(std::map<std::string, std::string> options, Transport&);
    Receiver(std::map<std::string, std::string> options, Transport&, Presentation&);
    ~Receiver();

    void sendDiscover();

    void addDataListener(DataObserver*);
    void removeDataListener(DataObserver*);

    void addControlListener(ControlObserver*);
    void removeControlListener(ControlObserver*);
private:
    // Disable copying
    Receiver(const Receiver &);
    Receiver &operator=(const Receiver &);
private:
    class ReceiverImpl;
    std::unique_ptr<ReceiverImpl> pimpl;
};

}

#endif
