#ifndef EITransport_H__
#define EITransport_H__

#include "EIPrerequisites.h"

#include <vector>

namespace EI
{

class PacketListener;

class EITOOLKIT_EXPORT Transport
{
public:
    enum Channel {ALL, DATA, COMMUNICATION};

    virtual ~Transport() {}

    virtual void sendPacket(Channel, std::vector<Byte> const& packet) = 0;
    virtual void addPacketListener(Channel, PacketListener&) = 0;
    virtual void removePacketListener(PacketListener&) = 0;
};

class EITOOLKIT_EXPORT PacketListener
{
public:
    virtual ~PacketListener() {}
    virtual void onPacket(Transport::Channel, std::vector<Byte> const&) = 0;
};

}

#endif
