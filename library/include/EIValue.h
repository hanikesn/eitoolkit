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

    Type getType();

    std::string asString();
    double asDouble();
private:
    class ValueImpl;
    ValueImpl* const pimpl;
};

}

#endif
