#include "EIDiscoveryMessage.h"

namespace EI
{

char const* const DiscoveryMessage::IDENTIFIER = "discover";

DiscoveryMessage::DiscoveryMessage(std::string const& sender)
    : Message(sender, DiscoveryMessage::IDENTIFIER)
{}

}
