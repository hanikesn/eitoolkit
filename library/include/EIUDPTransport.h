#ifndef EIUDPTransport_H__
#define EIUDPTransport_H__

#include "EIPrerequisites.h"
#include "EITransport.h"

#include <string>
#include <map>

namespace EI
{

/**
 * @brief UDPTransport is a Transport implementation using UDPv4.
 *
 * @nocopy
 */
class EITOOLKIT_EXPORT UDPTransport : public Transport
{
public:
   /**
    * @brief Constructs a UDPTransport object.
    * @param options The options used. Currently none are supported.
    */
    UDPTransport(StringMap const& options);
    /**
     * @note Will block when listeners are still registered.
     */
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
