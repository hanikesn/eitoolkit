#ifndef EIDescription_H
#define EIDescription_H

#include "EIPrerequisites.h"
#include "EIValue.h"

#include <string>
#include <map>

namespace EI
{

class EITOOLKIT_EXPORT DataSeriesInfo
{
public:
    enum Property {INTERPOLATABLE=1, STATEFUL=2, HIDDEN=4, HAS_MIN=8, HAS_MAX=16, HAS_MINMAX=24};
    DataSeriesInfo(Value::Type type, Property properties, const std::string& misc);
    DataSeriesInfo(Value::Type type, Property properties, const std::string& misc, double min, double max);

    std::string getMisc() const;

    Value::Type getType() const;

    Property getProperties() const;

    bool hasProperty(Property property) const;

    double getMin() const;
    double getMax() const;

};

class EITOOLKIT_EXPORT Description
{
public:
    Description(const std::string& device_type);
    Description(const Description& other);
    Description(Description&& other);
    ~Description();
    Description& operator=(Description other);

    std::string getDeviceType() const;

    void addDataSeries(const std::string& name, const DataSeriesInfo& info);
    std::map<std::string, std::pair<Value::Type, std::string> > values() const;

private:
    void swap(Description& other) throw ();

private:
    class DescriptionImpl;
    DescriptionImpl* pimpl;
};

}

#endif
