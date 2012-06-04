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

/**
 * @brief The DataListener class is used as a callback interface for received @ref DataMessage "DataMessages".
 */
class EITOOLKIT_EXPORT DataListener
{
public:
    virtual ~DataListener();

    /**
     * @brief The function called when a new DataMessage arrives.
     * @param msg The DataMessage.
     *
     * @warning This method will be called asynchronously. That means that the implementation has to be @ref threadsafe "thread-safe".
     */
    virtual void onMessage(DataMessage msg) = 0;
};

/**
 * @brief The CommunicationListener class is used as a callback interface for received @ref Message "Messages" on the communication channel.
 */
class EITOOLKIT_EXPORT CommunicationListener
{
public:
    virtual ~CommunicationListener();

    /**
     * @brief The function called when a new Message arrives on the communication channel.
     * @param msg The Message
     */
    virtual void onMessage(Message const& msg) = 0;
};

/**
 * @brief The Receiver class allows you to receive @ref Message "messages" via the EIToolkit.
 */
class EITOOLKIT_EXPORT Receiver
{
public:
    Receiver(StringMap const& options);
    Receiver(StringMap const& options, Transport& transport);
    Receiver(StringMap const& options, Transport& transport, Presentation& presentation);
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
