#ifndef EIDataPacket_H
#define EIDataPacket_H

#include "EIPacket.h"

#include <map>

namespace EI
{

class EITOOLKIT_EXPORT DataPacket : public Packet
{
public:
    DataPacket(std::string const& name);
    virtual ~DataPacket();

    void setString(std::string const&, std::string const&);
    std::string getString(std::string const&) const;
    std::map<std::string, std::string> const& getStringValues() const;

    void setDouble(std::string const&, double);
    double getDouble(std::string const&) const;
private:
    std::map<std::string, std::string> stringValues;
};

}

#endif
