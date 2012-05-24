#include "EIValue.h"

namespace EI
{

class Value::ValueImpl
{
public:
    Type type;
};

Value::Value(Value const& other)
    : pimpl(new ValueImpl(*other.pimpl))
{
}

Value::Value()
    : pimpl(new ValueImpl)
{
    pimpl->type = EMPTY;
}

Value::Value(std::string const& value)
    : pimpl(new ValueImpl)
{
    pimpl->type = DOUBLE;
}

Value::Value(double value)
    : pimpl(new ValueImpl)
{
    pimpl->type = STRING;
}

Value::~Value()
{
    delete pimpl;
}

Value::Type Value::getType()
{
    return pimpl->type;
}

std::string Value::asString()
{
    return "";
}

double Value::asDouble()
{
    return 0.0;
}

}
