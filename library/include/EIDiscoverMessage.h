#ifndef EIDiscoverMessage_H
#define EIDiscoverMessage_H

#include "EIPrerequisites.h"
#include "EIMessage.h"

#include <string>

namespace EI
{

class EITOOLKIT_EXPORT DiscoveryMessage : public Message
{
public:
    DiscoveryMessage(std::string const& sender);

    static char const* const IDENTIFIER;
};

}

#endif
