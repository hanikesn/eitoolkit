#include "EIPacket.h"

namespace EI
{

class Message::MessageImpl
{
public:
    MessageImpl(std::string const& sender, std::string const& msgtype)
        : sender(sender), msgtype(msgtype) {}
    const std::string sender;
    const std::string msgtype;
};

Message::Message(std::string const& sender, std::string const& msgtype)
    : pimpl(new MessageImpl(sender, msgtype))
{
}

Message::Message(Message const& other)
    : pimpl(new MessageImpl(other.getSender(), other.getMsgtype()))
{
}

Message::~Message()
{
    delete pimpl;
}

std::string const& Message::getSender() const
{
    return pimpl->sender;
}


std::string const& Message::getMsgtype() const
{
    return pimpl->msgtype;
}

}
