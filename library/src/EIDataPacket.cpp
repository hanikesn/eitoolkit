#include "EIDataPacket.h"

namespace EI
{

static const Value emptyValue;
char const* const DataPacket::IDENTIFIER = "data";

class DataPacket::DataPacketImpl
{
public:
    void set(std::string const&, Value const&);
    Value const& get(std::string const&) const;
    std::map<std::string, Value> const& getValues() const;
private:
    std::map<std::string, Value> values;
};

DataPacket::DataPacket(std::string const& sender) :
    Packet(sender, DataPacket::IDENTIFIER), pimpl(new DataPacketImpl())
{
}

DataPacket::DataPacket(DataPacket const& other) :
    Packet(other.getSender(), DataPacket::IDENTIFIER), pimpl(new DataPacketImpl(*other.pimpl))
{

}

DataPacket::~DataPacket()
{
    delete pimpl;
}

void DataPacket::setString(std::string const& key, std::string const& value)
{
    pimpl->set(key, Value(value));
}

std::string const& DataPacket::getString(std::string const& key) const
{
    return pimpl->get(key).asString();
}

void DataPacket::setDouble(std::string const& key, double value)
{
    pimpl->set(key, Value(value));
}

double DataPacket::getDouble(std::string const& key) const
{
    return pimpl->get(key).asDouble();
}

std::map<std::string, Value> const& DataPacket::getValues() const
{
    return pimpl->getValues();
}

void DataPacket::DataPacketImpl::set(const std::string & key, const Value & value)
{
    values.insert(std::pair<const std::string, Value>(key, value));
}

std::map<std::string, Value> const& DataPacket::DataPacketImpl::getValues() const
{
    return values;
}

Value const& DataPacket::DataPacketImpl::get(const std::string & key) const
{
    auto val = values.find(key);
    if(val != values.end())
        return val->second;
    else
        return emptyValue;
}

}
