#include "EIJSONPresentation.h"
#include "EIDataPacket.h"
#include "json_spirit.h"

namespace js = json_spirit;

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

static std::vector<Byte> encodeDataPacket(DataPacket const& p)
{
    js::mObject obj;
    js::mObject values;

    obj["msgtype"] = p.getMsgtype();
    obj["sender"] = p.getSender();

    auto stringValues = p.getStringValues();

    std::for_each(stringValues.begin(), stringValues.end(),
                  [&values](std::pair<const

                            std::string, std::string>& pair)
    {
                  values.insert(pair);
    });

    obj["values"] = values;

    auto result = js::write(obj);
    return std::move(std::vector<Byte>(std::begin(result), std::end(result)));
}

static std::vector<Byte> encodePacket(Packet const& p)
{
    js::mObject obj;

    obj["msgtype"] = p.getMsgtype();
    obj["sender"] = p.getSender();

    auto result = js::write(obj);
    return std::move(std::vector<Byte>(std::begin(result), std::end(result)));
}

std::vector<Byte> JSONPresentation::JSONPresentationImpl::encode(Packet const& p)
{
    if(p.getMsgtype() == "data") {
        return encodeDataPacket(dynamic_cast<DataPacket const&>(p));
    } else {
        return encodePacket(p);
    }
}

static std::shared_ptr<Packet> decodeDataPacket(js::mObject & obj)
{
    auto sender = obj["sender"].get_str();
    auto packet = std::make_shared<DataPacket>(sender);

    auto val = obj["values"].get_obj();

    std::for_each(val.begin(), val.end(),
                  [&packet](std::pair<const std::string, js::mValue>& v)
    {
                  if(v.second.type() ==  js::str_type)
                    packet->setString(v.first, v.second.get_str());
    });

    return packet;
}

std::shared_ptr<Packet> JSONPresentation::JSONPresentationImpl::decode(std::vector<Byte> const& bytes)
{
    std::string str(std::begin(bytes), std::end(bytes));
    js::mValue val;
    if(!js::read(str, val))
        throw std::exception();

    js::mObject& obj = val.get_obj();

    auto msgtype = obj["msgtype"].get_str();
    auto sender = obj["sender"].get_str();

    if(msgtype=="data")
        return decodeDataPacket(obj);
    else
        return std::make_shared<Packet>(sender, msgtype);
}

}
