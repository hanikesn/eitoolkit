#ifndef EITransport_H__
#define EITransport_H__

#include "EIPrerequisites.h"

#include <vector>

namespace EI
{

class BytePacketObserver;

class Transport
{
public:
    enum Type {ALL, DATA, CONTROL};

    virtual ~Transport();

    virtual void sendBytePacket(Type, std::vector<Byte>) = 0;
    // startet automatisch einen Thread o.ä. wenn es einen observer gibt und killt ihn auch wieder
    virtual void addBytePacketObserver(Type, BytePacketObserver*) = 0;
    virtual void removeBytePacketObserver(BytePacketObserver*) = 0;
};

}

#endif
