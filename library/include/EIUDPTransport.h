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

    virtual void sendPacket(Channel, std::vector<Byte>  const&);
    virtual void addPacketListener(Channel, PacketListener&);
    virtual void removePacketListener(PacketListener&);
private:
    class UDPTransportImpl;
    UDPTransportImpl* const pimpl;
};

}

#endif
