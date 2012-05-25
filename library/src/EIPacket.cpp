#include "EIPacket.h"

namespace EI
{

class Packet::PacketImpl
{
public:
    PacketImpl(std::string const& sender, std::string const& msgtype)
        : sender(sender), msgtype(msgtype) {}
    const std::string sender;
    const std::string msgtype;
};

Packet::Packet(std::string const& sender, std::string const& msgtype)
    : pimpl(new PacketImpl(sender, msgtype))
{
}

Packet::Packet(Packet const& other)
    : pimpl(new PacketImpl(other.getSender(), other.getMsgtype()))
{
}

Packet::~Packet()
{
    delete pimpl;
}

std::string const& Packet::getSender() const
{
    return pimpl->sender;
}


std::string const& Packet::getMsgtype() const
{
    return pimpl->msgtype;
}

}
