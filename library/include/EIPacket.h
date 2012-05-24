#ifndef EIPacket_H__
#define EIPacket_H__

#include "EIPrerequisites.h"

#include <string>

namespace EI
{

class EITOOLKIT_EXPORT Packet
{
public:
    Packet(std::string const& sender, std::string const& msgtype) : sender(sender), msgtype(msgtype) {}
    Packet(Packet const& other) : sender(other.getSender()), msgtype(other.getMsgtype()) {}
    virtual ~Packet() {}

    std::string getSender() const {return sender;}
    std::string getMsgtype() const {return msgtype;}
private:
    const std::string sender;
    const std::string msgtype;
};

}

#endif
