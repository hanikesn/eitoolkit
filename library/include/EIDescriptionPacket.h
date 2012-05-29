#ifndef EIDescriptionPacket_H
#define EIDescriptionPacket_H

#include "EIPrerequisites.h"
#include "EIPacket.h"
#include "EIDescription.h"

namespace EI
{

class EITOOLKIT_EXPORT DescriptionPacket : public Packet
{
public:
    DescriptionPacket(std::string const& sender, Description const& description);

    Description const& getDescription();

    static char const* const IDENTIFIER;

private:
    class DescriptionPacketImpl;
    DescriptionPacketImpl* pimpl;
};

}

#endif
