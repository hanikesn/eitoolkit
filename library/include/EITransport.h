#ifndef EITransport_H__
#define EITransport_H__

#include "EIPrerequisites.h"

#include <vector>

namespace EI
{

class BytePacketObserver;

class EITOOLKIT_EXPORT Transport
{
public:
    enum Type {ALL, DATA, CONTROL};

    virtual ~Transport() {}

    virtual void sendBytePacket(Type, std::vector<Byte> const& packet) = 0;
    virtual void addBytePacketObserver(Type, BytePacketObserver&) = 0;
    virtual void removeBytePacketObserver(BytePacketObserver&) = 0;
};

class EITOOLKIT_EXPORT BytePacketObserver
{
public:
    virtual ~BytePacketObserver() {}
    virtual void onBytePacket(Transport::Type, std::vector<Byte> const&) = 0;
};

}

#endif
