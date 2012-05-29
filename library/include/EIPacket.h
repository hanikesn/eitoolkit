#ifndef EIPacket_H__
#define EIPacket_H__

#include "EIPrerequisites.h"

#include <string>

namespace EI
{

class EITOOLKIT_EXPORT Packet
{
public:
    Packet(std::string const& sender, std::string const& msgtype);
    Packet(Packet const& other);
    virtual ~Packet();

    std::string const& getSender() const;
    std::string const& getMsgtype() const;
private:
    Packet& operator=(Packet const& other);
    class PacketImpl;
    PacketImpl* pimpl;
};

}

#endif
