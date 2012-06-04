#include <document.h>
#include <writer.h>
#include <stringbuffer.h>

#include "EIJSONPresentation.h"
#include "EIDataMessage.h"
#include "helpers.h"

#include <algorithm>
#include <iostream>
#include <memory>

namespace rs = rapidjson;

typedef rs::GenericDocument<rapidjson::UTF8<>, rapidjson::CrtAllocator> Document;
typedef rs::GenericValue<rapidjson::UTF8<>, rapidjson::CrtAllocator> Value;

namespace EI
{

class Wrapper
{
public:
    Wrapper(ByteVector& out) : out(out) {}
    ByteVector& out;
    
    void Put(char c)
    {
        out.push_back(c);
    }

    void Flush() {}
};

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

static void encodeDataMessage(DataMessage const& p, rs::Writer<Wrapper> & writer)
{
    writer.String("values");

    writer.StartObject();

    auto const& values = p.getContent();

    std::for_each(values.begin(), values.end(),
                  [&writer](std::pair<const std::string, Value> const& pair)
    {
            if(pair.second.getType() == Value::STRING) {
                writer.String(pair.first.c_str(), pair.first.length());
                auto & val = pair.second.asString();
                writer.String(val.c_str(), val.length());
            } else if(pair.second.getType() == Value::DOUBLE) {
                writer.String(pair.first.c_str(), pair.first.length());
                writer.Double(pair.second.asDouble());
            }
    });

    writer.EndObject();
}

void JSONPresentation::JSONPresentationImpl::encode(Message const& p, ByteVector& out)
{
    Wrapper buffer(out);
    rs::Writer<Wrapper> writer(buffer);
    auto msgtype = p.getMsgType();
    auto sender = p.getSender();

    writer.StartObject();
    writer.String("msgtype");
    writer.String(msgtype.c_str(), msgtype.length());
    writer.String("sender");
    writer.String(sender.c_str(), sender.length());

    if(p.getMsgType() == DataMessage::IDENTIFIER) {
        encodeDataMessage(dynamic_cast<DataMessage const&>(p), writer);
    }

    writer.EndObject();
}

static std::unique_ptr<Message> decodeDataMessage(Document const& doc, std::string sender)
{
    std::unique_ptr<DataMessage> packet(new DataMessage(sender));

    auto const& val = doc["values"];

    std::for_each(val.MemberBegin(), val.MemberEnd(),
        [&packet](::Value::Member const& v)
    {
                  if(v.value.IsString())
                      packet->setString(v.name.GetString(), v.value.GetString());
    });

    return std::move(packet);
}

std::unique_ptr<Message> JSONPresentation::JSONPresentationImpl::decode(ByteVector const& bytes)
{
    Document document;
    std::vector<Byte> buffer(bytes.size() + 1);
    buffer.assign(bytes.cbegin(), bytes.cend());
    buffer.push_back(0);
    if (document.ParseInsitu<1>(buffer.data()).HasParseError())
    {
        std::cerr << document.GetParseError() << ":" << document.GetErrorOffset() << "\n";
        throw std::exception();
    }

    std::string msgtype = document["msgtype"].GetString();
    std::string sender = document["sender"].GetString();

    if(msgtype==DataMessage::IDENTIFIER)
        return decodeDataMessage(document, sender);
    else
        return std::unique_ptr<Message>(new Message(sender, msgtype));
}

}
