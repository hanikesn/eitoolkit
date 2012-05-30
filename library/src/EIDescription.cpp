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

Description::~Description()
{
    delete pimpl;
}

Description::Description(Description const& other)
    : pimpl(new DescriptionImpl(*other.pimpl))
{
}

Description& Description::operator=(Description const& other)
{
    Description tmp(other);
    std::swap(pimpl, tmp.pimpl);
    return *this;
}

}
