#ifndef EIPresentation_H__
#define EIPresentation_H__

#include "EIPrerequisites.h"
#include "EIPacket.h"

#include <vector>
#include <cstdint>
#include <memory>

namespace EI
{

class EITOOLKIT_EXPORT Presentation
{
public:
    virtual ~Presentation() {}
    virtual std::vector<Byte> encode(Packet const&) = 0;
    virtual std::shared_ptr<Packet> decode(std::vector<Byte> const&) = 0;
};

}

#endif
