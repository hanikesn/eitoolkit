#include "EIDataPacket.h"

namespace EI
{

DataPacket::DataPacket(std::string const& sender) :
    Packet(sender, "data")
{
}

DataPacket::~DataPacket()
{
}

void DataPacket::setString(std::string const& key, std::string const& value)
{
    stringValues[key] = value;
}

std::string DataPacket::getString(std::string const& key) const
{
    return stringValues.find(key)->second;
}

void DataPacket::setDouble(std::string const&, double)
{
}

double DataPacket::getDouble(std::string const&) const
{
    return 0.0;
}

std::map<std::string, std::string> const& DataPacket::getStringValues() const
{
    return stringValues;
}

}
