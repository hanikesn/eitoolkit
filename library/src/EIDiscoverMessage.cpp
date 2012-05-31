#include "EIDiscoverMessage.h"

namespace EI
{

char const* const DiscoverMessage::IDENTIFIER = "discover";

DiscoverMessage::DiscoverMessage(std::string const& sender)
    : Message(sender, DiscoverMessage::IDENTIFIER)
{}

}
