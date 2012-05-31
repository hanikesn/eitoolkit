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

    std::string const& getSender() const;
    std::string const& getMsgType() const;

protected:
    // used to construct an empty Message
    Message(void *);
    void swap(Message& other) throw ();

private:
    class MessageImpl;
    MessageImpl* pimpl;
};

}

#endif
