#include "EIJSONPresentation.h"
#include "EIDataMessage.h"
#include "json_spirit.h"
#include "helpers.h"

namespace js = json_spirit;

namespace EI
{

class JSONPresentation::JSONPresentationImpl
{
public:
    JSONPresentationImpl(StringMap const& options);

    void encode(Message const&, ByteVector & out);
    std::unique_ptr<Message> decode(ByteVector const&);
};

JSONPresentation::JSONPresentation(StringMap const& options) :
    pimpl(new JSONPresentationImpl(options))
{}

JSONPresentation::~JSONPresentation()
{
    delete pimpl;
}

void JSONPresentation::encode(Message const& p, ByteVector & out)
{
    return pimpl->encode(p, out);
}

std::unique_ptr<Message> JSONPresentation::decode(ByteVector const& bytes)
{
    return pimpl->decode(bytes);
}

JSONPresentation::JSONPresentationImpl::JSONPresentationImpl(StringMap const&)
{}

static void encodeDataMessage(DataMessage const& p, ByteVector & out)
{
    js::mObject obj;
    js::mObject valuesObj;

    obj["msgtype"] = p.getMsgType();
    obj["sender"] = p.getSender();

    auto values = p.getContent();

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

static void encodeMessage(Message const& p, ByteVector & out)
{
    js::mObject obj;

    obj["msgtype"] = p.getMsgType();
    obj["sender"] = p.getSender();

    auto result = js::write(obj);
    out.assign(result.begin(), result.end());
}

void JSONPresentation::JSONPresentationImpl::encode(Message const& p, ByteVector& out)
{
    if(p.getMsgType() == DataMessage::IDENTIFIER) {
        encodeDataMessage(dynamic_cast<DataMessage const&>(p), out);
    } else {
        encodeMessage(p, out);
    }
}

static std::unique_ptr<Message> decodeDataMessage(js::mObject & obj)
{
    auto sender = obj["sender"].get_str();
    std::unique_ptr<DataMessage> packet(new DataMessage(sender));

    auto val = obj["values"].get_obj();

    std::for_each(val.begin(), val.end(),
                  [&packet](std::pair<const std::string, js::mValue>& v)
    {
                  if(v.second.type() ==  js::str_type)
                    packet->setString(v.first, v.second.get_str());
    });

    return std::move(packet);
}

std::unique_ptr<Message> JSONPresentation::JSONPresentationImpl::decode(ByteVector const& bytes)
{
    auto str = std::string(bytes.begin(), bytes.end());
    js::mValue val;
    if(!js::read(str, val))
        throw std::exception();

    js::mObject& obj = val.get_obj();

    auto msgtype = obj["msgtype"].get_str();
    auto sender = obj["sender"].get_str();

    if(msgtype==DataMessage::IDENTIFIER)
        return decodeDataMessage(obj);
    else
        return std::unique_ptr<Message>(new Message(sender, msgtype));
}

}
