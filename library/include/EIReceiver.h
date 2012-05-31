#ifndef EIReceiver_H__
#define EIReceiver_H__

#include "EIPrerequisites.h"
#include "EITransport.h"
#include "EIPresentation.h"
#include "EIDataMessage.h"

#include <map>
#include <string>

namespace EI
{

class EITOOLKIT_EXPORT DataListener
{
public:
    virtual ~DataListener();
    virtual void onMessage(DataMessage const&) = 0;
};

class EITOOLKIT_EXPORT CommunicationListener
{
public:
    virtual ~CommunicationListener();
    virtual void onMessage(Message const&) = 0;
};

class EITOOLKIT_EXPORT Receiver
{
public:
    Receiver(std::map<std::string, std::string> const& options);
    Receiver(std::map<std::string, std::string> const& options, Transport& transport);
    Receiver(std::map<std::string, std::string> const& options, Transport& transport, Presentation& presentation);
    ~Receiver();

    void discoverSenders();

    void addDataListener(DataListener& listener);
    void removeDataListener(DataListener& listener);

    void addCommunicationListener(CommunicationListener& listener);
    void removeCommunicationListener(CommunicationListener& listener);
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
