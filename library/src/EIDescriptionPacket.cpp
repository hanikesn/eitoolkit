#include "EIDescriptionPacket.h"

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
    : Message(sender, "description"), pimpl(new DescriptionMessageImpl(description))
{
}

}
