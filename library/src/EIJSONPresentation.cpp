#include "EIJSONPresentation.h"
#include "EIDataPacket.h"

namespace EI
{

class JSONPresentation::JSONPresentationImpl
{
public:
    JSONPresentationImpl(std::map<std::string, std::string> const& options);

    std::vector<Byte> encode(Packet const&);
    std::shared_ptr<Packet> decode(std::vector<Byte> const&);
};

JSONPresentation::JSONPresentation(std::map<std::string, std::string> const& options) :
    pimpl(new JSONPresentationImpl(options))
{}

JSONPresentation::~JSONPresentation()
{
    delete pimpl;
}

std::vector<Byte> JSONPresentation::encode(Packet const& p)
{
    return pimpl->encode(p);
}

std::shared_ptr<Packet> JSONPresentation::decode(std::vector<Byte> const& bytes)
{
    return pimpl->decode(bytes);
}

JSONPresentation::JSONPresentationImpl::JSONPresentationImpl(std::map<std::string, std::string> const& options)
{}

std::vector<Byte> encodeDataPacket(DataPacket const& p)
{
    std::vector<Byte> result;
    result.push_back(1);
    return result;
}

std::vector<Byte> JSONPresentation::JSONPresentationImpl::encode(Packet const& p)
{
    if(p.getType() == "data") {
        return encodeDataPacket(dynamic_cast<DataPacket const&>(p));
    }
    std::vector<Byte> result;
    result.push_back(0);
    return result;
}

std::shared_ptr<Packet> JSONPresentation::JSONPresentationImpl::decode(std::vector<Byte> const& bytes)
{
    if(bytes[0]== 0)
        return std::make_shared<Packet>("name", "type");
    else
        return std::make_shared<DataPacket>("name");
}

}
