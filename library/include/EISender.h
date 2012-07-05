#ifndef EISender_H__
#define EISender_H__

#include "EIPrerequisites.h"
#include "EITransport.h"
#include "EIPresentation.h"
#include "EIMessage.h"
#include "EIDataMessage.h"
#include "EIDescription.h"

#include <map>
#include <string>

namespace EI
{

/**
 * @brief The Sender class allows you to send @ref Message "messages" via the EIToolkit.
 *
 * Currently the default Transport is the UDPTransport and the default Presentation is the JSONPresentation.
 *
 * Options for the the Sender, Transport and Presentation can be configured via the options the parameter of the constuctor.
 *
 * @section Example
 * @code
 * EI::Sender sender(EI::Description("Sender"), EI::StringMap());
 * EI::DataMessage msg("Sender");
 * msg.setDouble("x", 42.0);
 * sender.sendMessage(msg);
 * @endcode
 *
 * @nocopy
 */
class EITOOLKIT_EXPORT Sender
{
public:
    /**
     * @brief Constructs a Sender object with the default Transport and Presentation.
     * @param description A Description object which specifies the properties of the Sender.
     * @param options Various options for the Sender. Will also be used for the construction of the default Transport and Presentation.
     */
    Sender(Description const& description, StringMap const& options);
    /**
     * @brief Constructs a Sender object wich uses the given Transport and Presentation.
     * @param description A Description object which specifies the properties of the Sender.
     * @param options Various options for the Sender.
     * @param transport The Transport to be used.
     * @param presentation The Presentation to be used.
     *
     * @warning The Transport and Presentation need to be valid for the lifetime of the Sender object.
     */
    Sender(Description const& description, StringMap const& options, Transport& transport, Presentation& presentation);
    ~Sender();

    /**
     * @brief Create a new DataMessage.
     */
    DataMessage createDataMessage();

    /**
     * @brief Sends a message.
     *
     * The message will be encoded with the presentation and then sent via the transport.
     *
     * The @ref Transport::Channel "Channel" on which the message will be sent is choosen automatically.
     *
     * @threadsafe
     *
     * @param msg The message to be sent.
     */
    void sendMessage(const Message& msg);
private:
    // Disable copying
    Sender(const Sender &);
    Sender &operator=(const Sender &);
private:
    class SenderImpl;
    SenderImpl* const pimpl;
};

}

#endif
