#ifndef EIDescriptionMessage_H
#define EIDescriptionMessage_H

#include "EIPrerequisites.h"
#include "EIMessage.h"
#include "EIDescription.h"

namespace EI
{

class EITOOLKIT_EXPORT DescriptionMessage : public Message
{
public:
    DescriptionMessage(std::string const& sender, Description const& description);

    virtual ~DescriptionMessage();
    DescriptionMessage(const DescriptionMessage & other);
    DescriptionMessage(DescriptionMessage && other);
    DescriptionMessage &operator=(DescriptionMessage other);

    Description getDescription() const;

    static char const* const IDENTIFIER;
private:
    void swap(DescriptionMessage& other) throw ();

private:
    class DescriptionMessageImpl;
    DescriptionMessageImpl* pimpl;
};

}

#endif
