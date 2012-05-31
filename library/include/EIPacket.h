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
    virtual ~Message();

    std::string const& getSender() const;
    std::string const& getMsgtype() const;
private:
    Message& operator=(Message const& other);
    class MessageImpl;
    MessageImpl* pimpl;
};

}

#endif
