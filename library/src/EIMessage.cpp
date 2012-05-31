#include "EIMessage.h"

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
    : pimpl(new MessageImpl(other.getSender(), other.getMsgType()))
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


std::string const& Message::getMsgType() const
{
    return pimpl->msgtype;
}

}
