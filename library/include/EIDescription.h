#ifndef EIDescription_H
#define EIDescription_H

#include "EIPrerequisites.h"
#include "EIValue.h"

#include <string>
#include <map>

namespace EI
{

class EITOOLKIT_EXPORT Description
{
public:
    Description();
    Description(Description const& other);
    ~Description();
    Description& operator=(Description const& other);

    void addDataStream(std::string const& name, std::pair<Value::Type, std::string> const& info);

    std::map<std::string, std::pair<Value::Type, std::string> > values();

private:
    class DescriptionImpl;
    DescriptionImpl* pimpl;
};

}

#endif
