#ifndef EIDataMessage_H
#define EIDataMessage_H

#include "EIPrerequisites.h"
#include "EIValue.h"
#include "EIMessage.h"

#include <map>

namespace EI
{

class EITOOLKIT_EXPORT DataMessage : public Message
{
public:
    static char const* const IDENTIFIER;

    DataMessage(std::string const& sender);
    DataMessage(DataMessage const& other);
    DataMessage(DataMessage && other);
    DataMessage& operator=(DataMessage other);
    ~DataMessage();

    void set(std::string const& name, Value const& value);
    Value const& get(std::string const& name) const;
    std::map<std::string, Value> getContent() const;

    void setString(std::string const& name, std::string const& value);
    std::string getString(std::string const& name) const;

    void setDouble(std::string const& name, double value);
    double getDouble(std::string const& name) const;

private:
    void swap(DataMessage& other) throw ();

private:
    class DataMessageImpl;
    DataMessageImpl* pimpl;
};

}

#endif
