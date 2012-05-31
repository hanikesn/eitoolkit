#ifndef EIUDPTransport_H__
#define EIUDPTransport_H__

#include "EIPrerequisites.h"
#include "EITransport.h"

#include <string>
#include <map>

namespace EI
{

class EITOOLKIT_EXPORT UDPTransport : public Transport
{
public:
    UDPTransport(std::map<std::string, std::string> const& options);
    virtual ~UDPTransport();

    virtual void sendPacket(Channel channel, std::vector<Byte> const& packet);
    virtual void addPacketListener(Channel channel, PacketListener& packet);
    virtual void removePacketListener(PacketListener& packet);
private:
    // Disable copying
    UDPTransport(const UDPTransport &);
    UDPTransport &operator=(const UDPTransport &);
private:
    class UDPTransportImpl;
    UDPTransportImpl* const pimpl;
};

}

#endif
