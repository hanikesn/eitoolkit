#include "EIDiscoverPacket.h"

namespace EI
{

char const* const DiscoverPacket::IDENTIFIER = "discover";

DiscoverPacket::DiscoverPacket(std::string const& sender)
    : Packet(sender, DiscoverPacket::IDENTIFIER)
{}

}
