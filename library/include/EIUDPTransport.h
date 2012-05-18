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
    UDPTransport(std::map<std::string, std::string> options);
    virtual ~UDPTransport();

    virtual void sendBytePacket(Type, std::vector<Byte>);
    virtual void addBytePacketObserver(Type, BytePacketObserver*);
    virtual void removeBytePacketObserver(BytePacketObserver*);
private:
    class UDPTransportImpl;
    UDPTransportImpl* const pimpl;
};

}

#endif