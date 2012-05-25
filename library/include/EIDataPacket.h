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
    DataPacket(std::string const& sender);
    DataPacket(DataPacket const& other);
    ~DataPacket();

    void set(std::string const&, Value const&);
    Value const& get(std::string const&) const;
    std::map<std::string, Value> const& getValues() const;

    void setString(std::string const&, std::string const&);
    std::string const& getString(std::string const&) const;

    void setDouble(std::string const&, double);
    double getDouble(std::string const&) const;
private:
    class DataPacketImpl;
    DataPacketImpl* const pimpl;
};

}

#endif
