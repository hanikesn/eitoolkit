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
    /**
     * @brief The Channel enum
     */
    enum Channel {ALL, DATA, COMMUNICATION};

    virtual ~Transport();

    virtual void sendPacket(Channel channel, ByteVector const& packet) = 0;
    virtual void addPacketListener(Channel channel, PacketListener& listener) = 0;
    virtual void removePacketListener(PacketListener& listener) = 0;
};

class EITOOLKIT_EXPORT PacketListener
{
public:
    virtual ~PacketListener();
    virtual void onPacket(Transport::Channel channel, ByteVector const& packet) = 0;
};

}

#endif
