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

Message::Message(void*)
    : pimpl(0)
{
}

Message::Message(Message const& other)
    : pimpl(new MessageImpl(other.getSender(), other.getMsgType()))
{
}

Message::Message(Message && other)
    : pimpl(0)
{
    swap(other);
}

Message::~Message()
{
    delete pimpl;
}

Message& Message::operator=(Message other)
{
    other.swap(*this);
    return *this;
}

void Message::swap(Message &other) throw ()
{
    std::swap(pimpl, other.pimpl);
}

std::string Message::getSender() const
{
    return pimpl->sender;
}


std::string Message::getMsgType() const
{
    return pimpl->msgtype;
}

}
