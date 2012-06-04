#ifndef EIDiscoveryMessage_H
#define EIDiscoveryMessage_H

#include "EIPrerequisites.h"
#include "EIMessage.h"

#include <string>

namespace EI
{

/**
 * @brief A message used to discover @ref Sender "Senders".
 *
 * This message is sent over the commuication channel if a Receiver wants to be informed about all the active \@ref Sender "Senders".
 *
 */
class EITOOLKIT_EXPORT DiscoveryMessage : public Message
{
public:
    /**
     * @brief IDENTIFIER The identifier used for the MsgType.
     */
    static char const* const IDENTIFIER;

    /**
     * @brief Constructs a new DiscoveryMessage object.
     * @param sender The sender of the message
     */
    DiscoveryMessage(std::string const& sender);
    /**
     * @copy_constructor
     */
    DiscoveryMessage(const DiscoveryMessage &);
    virtual ~DiscoveryMessage();
};

}

#endif
