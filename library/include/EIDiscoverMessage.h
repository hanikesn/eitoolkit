#ifndef EIDiscoverMessage_H
#define EIDiscoverMessage_H

#include "EIPrerequisites.h"
#include "EIMessage.h"

#include <string>

namespace EI
{

class EITOOLKIT_EXPORT DiscoverMessage : public Message
{
public:
    DiscoverMessage(std::string const& sender);

    static char const* const IDENTIFIER;
};

}

#endif
