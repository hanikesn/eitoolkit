#ifndef EIDiscoverPacket_H
#define EIDiscoverPacket_H

#include "EIPrerequisites.h"
#include "EIPacket.h"

#include <string>

namespace EI
{

class EITOOLKIT_EXPORT DiscoverPacket : public Packet
{
public:
    DiscoverPacket(std::string const& sender);

    static char const* const IDENTIFIER;
};

}

#endif
