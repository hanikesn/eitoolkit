#ifndef EIPresentation_H__
#define EIPresentation_H__

#include "EIPrerequisites.h"
#include "EIPacket.h"

#include <vector>
#include <cstdint>

namespace EI
{

class Presentation
{
public:
    virtual ~Presentation();
    virtual std::vector<Byte> encode(Packet) = 0;
    virtual Packet decode(std::vector<Byte>) = 0;
};

}

#endif
