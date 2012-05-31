#ifndef EIDiscoveryMessage_H
#define EIDiscoveryMessage_H

#include "EIPrerequisites.h"
#include "EIMessage.h"

#include <string>

namespace EI
{

class EITOOLKIT_EXPORT DiscoveryMessage : public Message
{
public:
    DiscoveryMessage(std::string const& sender);
    virtual ~DiscoveryMessage();

    static char const* const IDENTIFIER;
};

}

#endif
