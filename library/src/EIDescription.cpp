#include "EIDescription.h"

namespace EI
{

class Description::DescriptionImpl
{

};

Description::Description()
    : pimpl(new DescriptionImpl())
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
