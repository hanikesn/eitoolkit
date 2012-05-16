#ifndef IETransport_H__
#define IETransport_H__

#include "IEPrerequisites.h"

#include <vector>

namespace IE
{

class BytePacketObserver;

class Transport
{
    enum Type {ALL, DATA, CONTROL};

    virtual void sendBytePacket(Type, std::vector<Byte>) = 0;
    // startet automatisch einen Thread o.ä. wenn es einen observer gibt und killt ihn auch wieder
    virtual void addBytePacketObserver(Type, BytePacketObserver*) = 0;
    virtual void removeBytePacketObserver(BytePacketObserver*) = 0;
};

}

#endif
