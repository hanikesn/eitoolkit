#include "EIDescriptionMessage.h"

namespace EI
{

char const* const DescriptionMessage::IDENTIFIER = "description";

class DescriptionMessage::DescriptionMessageImpl
{
public:
    DescriptionMessageImpl(Description const& desc) : description(desc) {}

    Description description;
};

DescriptionMessage::DescriptionMessage(const std::string &sender, const Description &description)
    : Message(sender, DescriptionMessage::IDENTIFIER), pimpl(new DescriptionMessageImpl(description))
{
}

DescriptionMessage::DescriptionMessage(DescriptionMessage&& other)
    : Message(0), pimpl(0)
{
    swap(other);
}

DescriptionMessage& DescriptionMessage::operator=(DescriptionMessage other)
{
    swap(other);
    return *this;
}

DescriptionMessage::~DescriptionMessage()
{
    delete pimpl;
}

void DescriptionMessage::swap(DescriptionMessage &other) throw ()
{
    Message::swap(other);
    std::swap(pimpl, other.pimpl);
}

}
