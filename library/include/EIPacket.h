#ifndef EIPacket_H__
#define EIPacket_H__

#include "EIPrerequisites.h"

#include <string>

namespace EI
{

class EITOOLKIT_EXPORT Packet
{
public:
    Packet(std::string const& name, std::string const& type) : name(name), type(type) {}
    virtual ~Packet() {}

    std::string getName() const {return name;}
    std::string getType() const {return type;}
private:
    const std::string name;
    const std::string type;
};

}

#endif
