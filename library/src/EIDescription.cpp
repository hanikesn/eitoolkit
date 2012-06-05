#include "EIDescription.h"

namespace EI
{

class Description::DescriptionImpl
{
public:
    DescriptionImpl(const std::string& device_type) : device_type(device_type) {}
    const std::string device_type;
    DataSeriesInfoMap infos;
};

Description::Description(const std::string& device_type)
    : pimpl(new DescriptionImpl(device_type))
{
}

Description::Description(Description&& other)
    : pimpl(0)
{
    swap(other);
}

Description::~Description()
{
    delete pimpl;
}

Description::Description(Description const& other)
    : pimpl(new DescriptionImpl(*other.pimpl))
{
}

Description& Description::operator=(Description other)
{
    swap(other);
    return *this;
}

void Description::swap(Description &other) throw ()
{
    std::swap(pimpl, other.pimpl);
}

std::string Description::getDeviceType() const
{
    return pimpl->device_type;
}

void Description::addDataSeries(const std::string& name, const DataSeriesInfo& info)
{
    pimpl->infos.insert(std::pair<std::string, DataSeriesInfo>(name, info));
}

DataSeriesInfoMap Description::getDataSeries() const
{
    return pimpl->infos;
}

class DataSeriesInfo::DataSeriesInfoImpl
{
public:
    DataSeriesInfoImpl(Value::Type type, Properties properties, const std::string& misc, double min, double max)
        : type(type), properties(properties), misc(misc), min(min), max(max)
    {}

    DataSeriesInfoImpl(DataSeriesInfoImpl const& other)
        : type(other.type), properties(other.properties), misc(other.misc), min(other.min), max(other.max)
    {}

    const Value::Type type;
    const Properties properties;
    const std::string misc;
    const double min;
    const double max;
};




DataSeriesInfo::DataSeriesInfo(Value::Type type, Properties properties, const std::string& misc)
    : pimpl(new DataSeriesInfoImpl(type, properties, misc, 0.0, 0.0))
{

}

DataSeriesInfo::DataSeriesInfo(Value::Type type, Properties properties, const std::string& misc, double min, double max)
    : pimpl(new DataSeriesInfoImpl(type, properties, misc, min, max))
{

}

DataSeriesInfo::DataSeriesInfo(DataSeriesInfo const& other)
    : pimpl(new DataSeriesInfoImpl(*other.pimpl))
{

}

DataSeriesInfo::DataSeriesInfo(DataSeriesInfo && other)
    : pimpl(0)
{
    swap(other);
}

DataSeriesInfo& DataSeriesInfo::operator=(DataSeriesInfo other)
{
    swap(other);
    return *this;
}

DataSeriesInfo::~DataSeriesInfo()
{
    delete pimpl;
}

Value::Type DataSeriesInfo::getType() const
{
    return pimpl->type;
}

bool DataSeriesInfo::hasProperty(Property property) const
{
    return (pimpl->properties & property) != 0;
}

DataSeriesInfo::Properties DataSeriesInfo::getProperties() const
{
    return pimpl->properties;
}

std::string DataSeriesInfo::getMisc() const
{
    return pimpl->misc;
}

double DataSeriesInfo::getMin() const
{
    return pimpl->min;
}

double DataSeriesInfo::getMax() const
{
    return pimpl->max;
}

void DataSeriesInfo::swap(DataSeriesInfo& other) throw ()
{
    std::swap(pimpl, other.pimpl);
}

DataSeriesInfo::DataSeriesInfo()
    : pimpl(new DataSeriesInfoImpl(Value::EMPTY, NONE, "", 0, 0))
{

}

}
