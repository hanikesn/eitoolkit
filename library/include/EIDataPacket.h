#ifndef EIDataMessage_H
#define EIDataMessage_H

#include "EIPrerequisites.h"
#include "EIValue.h"
#include "EIPacket.h"

#include <map>

namespace EI
{

class EITOOLKIT_EXPORT DataMessage : public Packet
{
public:
    static char const* const IDENTIFIER;

    DataMessage(std::string const& sender);
    DataMessage(DataMessage const& other);
    ~DataMessage();

    // needed for the bindings of BlockingReceiver (std::vector<DataMessage>)
    DataMessage& operator=(DataMessage const& other);

    void set(std::string const& name, Value const& value);
    Value const& get(std::string const& name) const;
    std::map<std::string, Value> getValues() const;

    void setString(std::string const& name, std::string const& value);
    std::string getString(std::string const& name) const;

    void setDouble(std::string const& name, double value);
    double getDouble(std::string const& name) const;

private:
    class DataMessageImpl;
    DataMessageImpl* pimpl;
};

}

#endif
