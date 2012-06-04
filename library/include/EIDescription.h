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
    enum Property {
        NONE=0,
        INTERPOLATABLE=1<<0,
        STATEFUL=1<<2,
        HIDDEN=1<<3,
        HAS_MIN=1<<4,
        HAS_MAX=1<<5,
        HAS_MINMAX=HAS_MIN | HAS_MAX
    };

    // Don't use this exists only for the brocken swig bindings
    EITOOLKIT_DEPRECATED DataSeriesInfo();
    DataSeriesInfo(Value::Type type, Property properties, const std::string& misc);
    DataSeriesInfo(Value::Type type, Property properties, const std::string& misc, double min, double max);

    DataSeriesInfo(DataSeriesInfo const& other);
    DataSeriesInfo(DataSeriesInfo && other);
    DataSeriesInfo& operator=(DataSeriesInfo other);
    ~DataSeriesInfo();

    Value::Type getType() const;

    bool hasProperty(Property property) const;
    Property getProperties() const;

    std::string getMisc() const;

    double getMin() const;
    double getMax() const;

private:
    void swap(DataSeriesInfo& other) throw ();

private:
    class DataSeriesInfoImpl;
    DataSeriesInfoImpl* pimpl;
};

/**
 * @brief A map from std::string to DataSeriesInfo.
 */
typedef std::map<std::string, DataSeriesInfo> DataSeriesInfoMap;

/**
 * @brief Provides information about a Sender.
 */
class EITOOLKIT_EXPORT Description
{
public:
    Description(const std::string& device_type);

    Description(const Description& other);
    Description(Description&& other);
    Description& operator=(Description other);
    ~Description();

    std::string getDeviceType() const;

    void addDataSeries(const std::string& name, const DataSeriesInfo& info);
    DataSeriesInfoMap getDataSeries() const;

private:
    void swap(Description& other) throw ();

private:
    class DescriptionImpl;
    DescriptionImpl* pimpl;
};

}

#endif
