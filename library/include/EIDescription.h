#ifndef EIDescription_H
#define EIDescription_H

#include "EIPrerequisites.h"
#include "EIValue.h"

#include <string>
#include <map>

namespace EI
{

/**
 * @brief Holds information about a data series of a Sender.
 *
 * A data series is a stream of information a Sender is publishing.
 *
 * For example an accelerometer has three data series: "x", "y", "z". Each of Type::Double and the flags INTERPOLATABLE and HAS_MINMAX set.
 */
class EITOOLKIT_EXPORT DataSeriesInfo
{
public:
    /**
     * @brief Flags that can be set for a data series.
     */
    enum Property {
        NONE=0,
        INTERPOLATABLE=1<<0,
        STATEFUL=1<<2,
        HIDDEN=1<<3,
        HAS_MIN=1<<4,
        HAS_MAX=1<<5,
        HAS_MINMAX=HAS_MIN | HAS_MAX
    };

    /**
     * @brief A bitset for Property.
     */
    typedef int Properties;

    /**
     * @brief Constructs a DataSeriesInfo object.
     * @param type The Value::Type of the data being sent.
     * @param properties The properties of the data being sent.
     * @param misc Miscellaneous information about the data series.
     */
    DataSeriesInfo(Value::Type type, Properties properties, const std::string& misc);
    /**
     * @brief Constructs a DataSeriesInfo object.
     * @param type The Value::Type of the data being sent.
     * @param properties The properties of the data being sent.
     * @param misc Miscellaneous information about the data series.
     * @param min The minimum value of the data series.
     * @param max The maximum value of the data series.
     */
    DataSeriesInfo(Value::Type type, Properties properties, const std::string& misc, double min, double max);

    /**
     * @copy_constructor
     */
    DataSeriesInfo(DataSeriesInfo const& other);
    /**
     * @move_constructor
     */
    DataSeriesInfo(DataSeriesInfo && other);
    /**
     * @assignment_operator
     */
    DataSeriesInfo& operator=(DataSeriesInfo other);
    ~DataSeriesInfo();

    /**
     * @brief Get the Value::Type of the data being sent.
     */
    Value::Type getType() const;
    /**
     * @brief Check wether the data series has the given Property.
     */
    bool hasProperty(Property property) const;
    /**
     * @brief Get a bitset with all the appropriate properties set.
     */
    Properties getProperties() const;
    /**
     * @brief Get miscellaneous information.
     */
    std::string getMisc() const;
    /**
     * @brief Get the minium value of the data being sent. Only valid if it has the property HAS_MIN.
     */
    double getMin() const;
    /**
     * @brief Get the maximum value of the data being sent. Only valid if it has the property HAS_MAX.
     */
    double getMax() const;

    // Don't use this exists only for the brocken swig bindings
    EITOOLKIT_DEPRECATED DataSeriesInfo();
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
    /**
     * @brief Constructs Description object.
     * @param sender The name of the sender.
     * @param device_type The type of the device. E.g.: "Kinect", "Accelerometer" etc.
     */
    Description(std::string const& sender, std::string const& device_type);
    /**
     * @brief Copy constructor
     */
    Description(Description const& other);
    /**
     * @brief Move constructor
     */
    Description(Description&& other);
    /**
     * @brief Assigment operator
     */
    Description& operator=(Description other);
    ~Description();

    /**
     * @brief Get the name of the sender.
     */
    std::string getSender() const;
    /**
     * @brief Get the type of the device. E.g.: "Kinect", "Accelerometer" etc.
     */
    std::string getDeviceType() const;
    /**
     * @brief Add information about a data series to this description.
     * @param name The name of the DataSeries.
     * @param info The DataSeriesInfo object.
     */
    void addDataSeries(const std::string& name, const DataSeriesInfo& info);
    /**
     * @brief Get a map of the contained DataSeries.
     */
    DataSeriesInfoMap getDataSeries() const;

private:
    void swap(Description& other) throw ();

private:
    class DescriptionImpl;
    DescriptionImpl* pimpl;
};

}

#endif
