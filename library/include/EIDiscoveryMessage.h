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
    static char const* const IDENTIFIER;

    DiscoveryMessage(std::string const& sender);
    DiscoveryMessage(const DiscoveryMessage &);
    virtual ~DiscoveryMessage();
};

}

#endif
