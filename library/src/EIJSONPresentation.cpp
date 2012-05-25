#include "EIJSONPresentation.h"
#include "EIDataPacket.h"
#include "json_spirit.h"

namespace js = json_spirit;

struct wrap_vector_as_istream : std::streambuf
{
    wrap_vector_as_istream(std::vector<EI::Byte> & vec ) {
        this->setg(&vec[0], &vec[0], &vec[0]+vec.size() );
    }
};

namespace EI
{

class JSONPresentation::JSONPresentationImpl
{
public:
    JSONPresentationImpl(std::map<std::string, std::string> const& options);

    void encode(Packet const&, std::vector<Byte> & out);
    std::shared_ptr<Packet> decode(std::vector<Byte> const&);
};

JSONPresentation::JSONPresentation(std::map<std::string, std::string> const& options) :
    pimpl(new JSONPresentationImpl(options))
{}

JSONPresentation::~JSONPresentation()
{
    delete pimpl;
}

void JSONPresentation::encode(Packet const& p, std::vector<Byte> & out)
{
    return pimpl->encode(p, out);
}

std::shared_ptr<Packet> JSONPresentation::decode(std::vector<Byte> const& bytes)
{
    return pimpl->decode(bytes);
}

JSONPresentation::JSONPresentationImpl::JSONPresentationImpl(std::map<std::string, std::string> const&)
{}

static void encodeDataPacket(DataPacket const& p, std::vector<Byte> & out)
{
    js::mObject obj;
    js::mObject valuesObj;

    obj["msgtype"] = p.getMsgtype();
    obj["sender"] = p.getSender();

    auto values = p.getValues();

    std::for_each(values.begin(), values.end(),
                  [&valuesObj](std::pair<const std::string, Value>& pair)
    {
            if(pair.second.getType() == Value::STRING)
                valuesObj[pair.first] = pair.second.asString();
            else if(pair.second.getType() == Value::DOUBLE)
                valuesObj[pair.first] = pair.second.asDouble();
    });

    obj["values"] = valuesObj;

    auto result = js::write(obj);
    out.assign(result.begin(), result.end());
}

static void encodePacket(Packet const& p, std::vector<Byte> & out)
{
    js::mObject obj;

    obj["msgtype"] = p.getMsgtype();
    obj["sender"] = p.getSender();

    auto result = js::write(obj);
    out.assign(result.begin(), result.end());
}

void JSONPresentation::JSONPresentationImpl::encode(Packet const& p, std::vector<Byte>& out)
{
    if(p.getMsgtype() == "data") {
        encodeDataPacket(dynamic_cast<DataPacket const&>(p), out);
    } else {
        encodePacket(p, out);
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
    auto str = std::string(bytes.begin(), bytes.end());
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
