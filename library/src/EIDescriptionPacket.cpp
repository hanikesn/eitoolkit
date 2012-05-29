#include "EIDescriptionPacket.h"

namespace EI
{

char const* const DescriptionPacket::IDENTIFIER = "description";

class DescriptionPacket::DescriptionPacketImpl
{
public:
    DescriptionPacketImpl(Description const& desc) : description(desc) {}

    Description description;
};

DescriptionPacket::DescriptionPacket(const std::string &sender, const Description &description)
    : Packet(sender, "description"), pimpl(new DescriptionPacketImpl(description))
{
}

}
