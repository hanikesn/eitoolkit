#ifndef EITransport_H__
#define EITransport_H__

#include "EIPrerequisites.h"

#include <vector>

namespace EI
{

class PacketObserver;

class EITOOLKIT_EXPORT Transport
{
public:
    enum Type {ALL, DATA, CONTROL};

    virtual ~Transport() {}

    virtual void sendPacket(Type, std::vector<Byte> const& packet) = 0;
    virtual void addPacketObserver(Type, PacketObserver&) = 0;
    virtual void removePacketObserver(PacketObserver&) = 0;
};

class EITOOLKIT_EXPORT PacketObserver
{
public:
    virtual ~PacketObserver() {}
    virtual void onPacket(Transport::Type, std::vector<Byte> const&) = 0;
};

}

#endif
