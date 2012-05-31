#include "EIValue.h"
#include "boost/variant.hpp"

namespace EI
{

class Value::ValueImpl
{
public:
    ValueImpl() : type(EMPTY) {}
    ValueImpl(double val) : type(DOUBLE), value(val) {}
    ValueImpl(std::string const& val) : type(STRING), value(val) {}
    ValueImpl(ValueImpl const& other) : type(other.type), value(other.value) {}

    const Type type;
    const boost::variant< double, std::string > value;
};

Value::Value(Value const& other)
    : pimpl(new ValueImpl(*other.pimpl))
{
}

Value::Value()
    : pimpl(new ValueImpl)
{
}

Value::Value(Value&& other)
    : pimpl(0)
{
    swap(other);
}

Value::Value(std::string const& value)
    : pimpl(new ValueImpl(value))
{
}

Value::Value(double value)
    : pimpl(new ValueImpl(value))
{
}

void Value::swap(Value &other) throw ()
{
    std::swap(pimpl, other.pimpl);
}

Value& Value::operator=(Value other)
{
    swap(other);
    return *this;
}

Value::~Value()
{
    delete pimpl;
}

Value::Type Value::getType() const
{
    return pimpl->type;
}

static const std::string empty;

std::string const& Value::asString() const
{
    if(pimpl->type == STRING)
        return boost::get<std::string const&>(pimpl->value);
    else
        return empty;
}

double Value::asDouble() const
{
    if(pimpl->type == DOUBLE)
        return boost::get<double>(pimpl->value);
    else
        return 0.0;
}

std::ostream& operator<< (std::ostream& stream, const Value& value)
{
    switch(value.getType()) {
    case Value::DOUBLE:
        stream << value.asDouble();
        break;
    case Value::STRING:
        stream << value.asString();
        break;
    default:
        break;
    }

    return stream;
}

}
