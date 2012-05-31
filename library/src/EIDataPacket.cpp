#include "EIDataPacket.h"

namespace EI
{

static const Value emptyValue;
char const* const DataMessage::IDENTIFIER = "data";

class DataMessage::DataMessageImpl
{
public:
    void set(std::string const&, Value const&);
    Value const& get(std::string const&) const;
    std::map<std::string, Value> const& getValues() const;
private:
    std::map<std::string, Value> values;
};

DataMessage::DataMessage(std::string const& sender) :
    Packet(sender, DataMessage::IDENTIFIER), pimpl(new DataMessageImpl())
{
}

DataMessage::DataMessage(DataMessage const& other) :
    Packet(other.getSender(), DataMessage::IDENTIFIER), pimpl(new DataMessageImpl(*other.pimpl))
{

}

DataMessage::~DataMessage()
{
    delete pimpl;
}

DataMessage& DataMessage::operator=(DataMessage const& other)
{
    DataMessage tmp(other);

    std::swap(pimpl, tmp.pimpl);

    return *this;
}

void DataMessage::setString(std::string const& key, std::string const& value)
{
    pimpl->set(key, Value(value));
}

std::string DataMessage::getString(std::string const& key) const
{
    return pimpl->get(key).asString();
}

void DataMessage::setDouble(std::string const& key, double value)
{
    pimpl->set(key, Value(value));
}

double DataMessage::getDouble(std::string const& key) const
{
    return pimpl->get(key).asDouble();
}

std::map<std::string, Value> DataMessage::getValues() const
{
    return pimpl->getValues();
}

void DataMessage::DataMessageImpl::set(const std::string & key, const Value & value)
{
    values.insert(std::pair<const std::string, Value>(key, value));
}

std::map<std::string, Value> const& DataMessage::DataMessageImpl::getValues() const
{
    return values;
}

Value const& DataMessage::DataMessageImpl::get(const std::string & key) const
{
    auto val = values.find(key);
    if(val != values.end())
        return val->second;
    else
        return emptyValue;
}

}
