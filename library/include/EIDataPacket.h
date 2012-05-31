#ifndef EIDataPacket_H
#define EIDataPacket_H

#include "EIPrerequisites.h"
#include "EIValue.h"
#include "EIPacket.h"

#include <map>

namespace EI
{

class EITOOLKIT_EXPORT DataPacket : public Packet
{
public:
    static char const* const IDENTIFIER;

    DataPacket(std::string const& sender);
    DataPacket(DataPacket const& other);
    ~DataPacket();

    // needed for the bindings of BlockingReceiver (std::vector<DataPacket>)
    DataPacket& operator=(DataPacket const& other);

    void set(std::string const& name, Value const& value);
    Value const& get(std::string const& name) const;
    std::map<std::string, Value> getValues() const;

    void setString(std::string const& name, std::string const& value);
    std::string getString(std::string const& name) const;

    void setDouble(std::string const& name, double value);
    double getDouble(std::string const& name) const;

private:
    class DataPacketImpl;
    DataPacketImpl* pimpl;
};

}

#endif
