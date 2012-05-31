#ifndef EIDescriptionMessage_H
#define EIDescriptionMessage_H

#include "EIPrerequisites.h"
#include "EIPacket.h"
#include "EIDescription.h"

namespace EI
{

class EITOOLKIT_EXPORT DescriptionMessage : public Message
{
public:
    DescriptionMessage(std::string const& sender, Description const& description);

    Description const& getDescription();

    static char const* const IDENTIFIER;

private:
    class DescriptionMessageImpl;
    DescriptionMessageImpl* pimpl;
};

}

#endif
