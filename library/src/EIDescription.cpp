#include "EIDescription.h"

namespace EI
{

class Description::DescriptionImpl
{
public:
    DescriptionImpl(const std::string& device_type) : device_type(device_type) {}
    const std::string device_type;
};

Description::Description(const std::string& device_type)
    : pimpl(new DescriptionImpl(device_type))
{
}

Description::Description(Description&& other)
    : pimpl(0)
{
    swap(other);
}

Description::~Description()
{
    delete pimpl;
}

Description::Description(Description const& other)
    : pimpl(new DescriptionImpl(*other.pimpl))
{
}

Description& Description::operator=(Description other)
{
    swap(other);
    return *this;
}

void Description::swap(Description &other) throw ()
{
    std::swap(pimpl, other.pimpl);
}

}
