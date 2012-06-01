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
    UDPTransport(StringMap const& options);
    virtual ~UDPTransport();

    virtual void sendPacket(Channel channel, ByteVector const& packet);
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
