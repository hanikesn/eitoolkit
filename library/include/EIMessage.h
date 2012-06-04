#ifndef EIMessage_H__
#define EIMessage_H__

#include "EIPrerequisites.h"

#include <string>

namespace EI
{

/**
 * @brief Base class of messages that can be sent via the EIToolkit.
 *
 * The MsgType attribute is used to identify the different kinds of messages. It is mainly used for encoding and decoding.
 */
class EITOOLKIT_EXPORT Message
{
public:
    /**
     * @brief Constructs a message object with the given sender and MsgType
     * @param sender The sender of the message
     * @param msg_type The type of the message
     */
    Message(std::string const& sender, std::string const& msg_type);
    /**
     * @brief Copy constructor.
     */
    Message(Message const& other);
    /**
     * @brief Move constructor.
     */
    Message(Message&& other);
    /**
     * @brief Assignment operator
     */
    Message& operator=(Message other);
    virtual ~Message();

    /**
     * @brief Get the sender of the message.
     */
    std::string getSender() const;
    /**
     * @brief Get the Type of the message.
     *
     * The type can be used to determine to what other class this message can be downcast to.
     */
    std::string getMsgType() const;

protected:
    /**
     * @brief Constructs a empty Message object.
     * @note Should only be used for move construction.
     */
    Message(void*);
    /**
     * @brief Swaps the contents of two Message objects.
     */
    void swap(Message& other) throw ();

private:
    class MessageImpl;
    MessageImpl* pimpl;
};

}

#endif
