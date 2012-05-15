#ifndef IEPresentation_H__
#define IEPresentation_H__

#include "IEPrerequisites.h"
#include "IEPacket.h"

#include <vector>
#include <cstdint>

namespace IE
{

class Presentation
{
    virtual std::vector<Byte> encode(Packet) = 0;
    virtual Packet decode(std::vector<Byte>) = 0;
};

}

#endif
