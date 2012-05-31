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
    Value(std::string const& value);
    Value(double value );

    Value(Value&& other);
    Value(Value const& other);
    Value& operator=(Value other);
    ~Value();

    Type getType() const;

    std::string const& asString() const;
    double asDouble() const;

private:
    void swap(Value& other) throw ();

private:
    class ValueImpl;
    ValueImpl* pimpl;
};

EITOOLKIT_EXPORT std::ostream& operator<< (std::ostream& stream, const Value& value);

}

#endif
