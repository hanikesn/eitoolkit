#ifndef EIValue_H
#define EIValue_H

#include "EIPrerequisites.h"

#include <string>

namespace EI
{

class EITOOLKIT_EXPORT Value
{
public:
    enum Type {EMPTY, DOUBLE, STRING};

    Value();
    Value(std::string const&);
    Value(double);
    Value(Value const&);
    ~Value();

    Type getType() const;

    std::string const& asString() const;
    double asDouble() const;
private:
    class ValueImpl;
    ValueImpl* const pimpl;
};

}

#endif
