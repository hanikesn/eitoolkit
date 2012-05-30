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
    virtual void encode(Packet const& msg, std::vector<Byte>& out_buffer) = 0;
    virtual std::shared_ptr<Packet> decode(std::vector<Byte> const& in_buffer) = 0;
};

}

#endif
