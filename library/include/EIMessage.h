#ifndef EIMessage_H__
#define EIMessage_H__

#include "EIPrerequisites.h"

#include <string>

namespace EI
{

class EITOOLKIT_EXPORT Message
{
public:
    Message(std::string const& sender, std::string const& msg_type);
    Message(Message const& other);
    Message(Message&& other);
    Message& operator=(Message other);
    virtual ~Message();

    std::string getSender() const;
    std::string getMsgType() const;

protected:
    /**
     * @brief Constructs a empty Message object.
     * @note Should only be used for move construction.
     */
    Message(void *);
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
