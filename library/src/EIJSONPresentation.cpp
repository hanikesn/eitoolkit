#include "EIJSONPresentation.h"

namespace EI
{

class JSONPresentation::JSONPresentationImpl
{
public:
    JSONPresentationImpl(std::map<std::string, std::string> options);

    std::vector<Byte> encode(Packet);
    Packet decode(std::vector<Byte>);
};

JSONPresentation::JSONPresentation(std::map<std::string, std::string> options) :
    pimpl(new JSONPresentationImpl(options))
{}

JSONPresentation::~JSONPresentation()
{
    delete pimpl;
}

std::vector<Byte> JSONPresentation::encode(Packet p)
{
    return pimpl->encode(p);
}

Packet JSONPresentation::decode(std::vector<Byte> bytes)
{
    return pimpl->decode(bytes);
}

JSONPresentation::JSONPresentationImpl::JSONPresentationImpl(std::map<std::string, std::string> options)
{}

std::vector<Byte> JSONPresentation::JSONPresentationImpl::encode(Packet p)
{
    std::vector<Byte> result;
    result.push_back(0);
    return result;
}

Packet JSONPresentation::JSONPresentationImpl::decode(std::vector<Byte> bytes)
{
    return Packet();
}

}
