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
 * @brief A callback interface for @ref DataMessage "DataMessages" used by the Receiver class.
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
 * @brief A callback interface for @ref Message "Messages" used by the Receiver class.
 */
class EITOOLKIT_EXPORT CommunicationListener
{
public:
    virtual ~CommunicationListener();

    /**
     * @brief The function called when a new Message arrives on the communication channel.
     * @param msg The Message. \warning The Message object will be destroyed after this method returns. It is therefore unsafe to safe references to the Message object.
     *
     * @warning This method will be called asynchronously. That means that the implementation has to be @ref threadsafe "thread-safe".
     */
    virtual void onMessage(Message const& msg) = 0;
};

/**
 * @brief The Receiver class allows you to receive @ref Message "messages" via the EIToolkit.
 *
 * @section Example
 * @code
 * #include <EIToolkit.h>
 * #include <iostream>
 *
 * class ExampleListener : public EI::DataListener
 * {
 * public:
 *     void onMessage(EI::DataMessage p) {
 *     }
 * };
 *
 * int main()
 * {
 *     ExampleListener listener;
 *     EI::StringMap options;
 *     EI::Receiver receiver(otions);
 *     receiver.addDataListener(listener);
 *
 *     // wait for input, so we don't quit immediately
 *     std::cin.get();
 * }
 * @endcode
 *
 * @warning Listeners should not be added or removed in the callback of a listener. Otherwise a deadlock will occur.
 *
 * @nocopy
 */
class EITOOLKIT_EXPORT Receiver
{
public:
    /**
     * @brief Constructs a Receiver object with the default Transport and the Presentation will be choosen automatically for each Message.
     * @param options Various options for the Receiver. Will also be used for the construction of the default Transport and Presentation.
     */
    Receiver(StringMap const& options);
    /**
     * @brief Constructs a Receiver object wich uses the given Transport. The Presentation will be choosen automatically for each Message.
     * @param options Various options for the Receiver. Will also be used for the construction of the Presentation.
     * @param transport The Transport to be used.
     */
    Receiver(StringMap const& options, Transport& transport);
    /**
     * @brief Constructs a Receiver object wich uses the given Transport and Presentation.
     * @param options Various options for the Receiver.
     * @param transport The Transport to be used.
     * @param presentation The Presentation to be used.
     */
    Receiver(StringMap const& options, Transport& transport, Presentation& presentation);
    ~Receiver();

    /**
     * @brief Tells the Receiver to look for @ref Sender "Senders" in the system.
     *
     * The Receiver will broadcast a DiscoverMessage. Any listening Sender will respond with a DescriptionMessage over the communication channel.
     * If you want to receive those you need to provide a CommunicationListener.
     *
     * @threadsafe
     */
    void discoverSenders();

    /**
     * @brief Add a listener for @ref DataMessage DataMessages.
     *
     * The listener will be asynchronously called when a new DataMessage arrives.
     *
     * @param listener The listener should live as long as the Receiver or should be removed before the Receiver is destroyed.
     * @threadsafe
     */
    void addDataListener(DataListener& listener);
    /**
     * @brief Remove a DataListener.
     * @threadsafe
     */
    void removeDataListener(DataListener& listener);

    /**
     * @brief Add a listener for @ref Message Messages on the communication channel.
     *
     * The listener will be asynchronously called when a new Message arrives.
     *
     * @param listener The listener should live as long as the Receiver or should be removed before the Receiver is destroyed.
     * @threadsafe
     */
    void addCommunicationListener(CommunicationListener& listener);
    /**
     * @brief Remove a CommunicationListener.
     * @threadsafe
     */
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
