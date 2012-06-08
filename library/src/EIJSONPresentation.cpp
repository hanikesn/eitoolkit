#include <document.h>
#include <writer.h>
#include <stringbuffer.h>

#include "EIJSONPresentation.h"
#include "EIDataMessage.h"
#include "EIDescriptionMessage.h"
#include "helpers.h"

#include <algorithm>
#include <iostream>
#include <memory>

namespace rs = rapidjson;

typedef rs::GenericDocument<rapidjson::UTF8<>, rapidjson::CrtAllocator> Document;
typedef rs::GenericValue<rapidjson::UTF8<>, rapidjson::CrtAllocator> Value;

namespace EI
{

const Byte JSONPresentation::IDENTIFIER;

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
};

JSONPresentation::JSONPresentation(StringMap const& options) :
    pimpl(new JSONPresentationImpl(options))
{}

JSONPresentation::~JSONPresentation()
{
    delete pimpl;
}

JSONPresentation::JSONPresentationImpl::JSONPresentationImpl(StringMap const&)
{}

Byte JSONPresentation::getIdentifier()
{
    return IDENTIFIER;
}

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

static void encodeDescriptionMessage(DescriptionMessage const& p, rs::Writer<Wrapper> & writer)
{
    writer.String("device");
    writer.String(p.getDescription().getDeviceType().c_str());

    writer.String("values");
    writer.StartObject();

    auto const& values = p.getDescription().getDataSeries();

    std::for_each(values.begin(), values.end(),
                  [&writer](std::pair<const std::string, DataSeriesInfo> const& pair)
    {
            auto const& d = pair.second;
            writer.String(pair.first.c_str());
            writer.StartObject();
            writer.String("type");
            switch(d.getType())
            {
            case Value::STRING:
                writer.String("STRING");
                break;
            case Value::DOUBLE:
                writer.String("DOUBLE");
                break;
            default:
                writer.String("EMPTY");
                break;
            }
            writer.String("properties");
            writer.Int(d.getProperties());
            writer.String("misc");
            writer.String(d.getMisc().c_str());
            writer.String("min");
            writer.Double(d.getMin());
            writer.String("max");
            writer.Double(d.getMax());
            writer.EndObject();
    });

    writer.EndObject();
}

void JSONPresentation::encode(Message const& p, ByteVector& out)
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
    } else if(p.getMsgType() == DescriptionMessage::IDENTIFIER) {
        encodeDescriptionMessage(dynamic_cast<DescriptionMessage const&>(p), writer);
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

static std::unique_ptr<Message> decodeDescriptionMessage(Document const& doc, std::string sender)
{
    std::string device = doc["device"].GetString();

    auto const& val = doc["values"];
    if(!val.IsObject())
        throw std::exception();

    Description desc(device);

    std::for_each(val.MemberBegin(), val.MemberEnd(),
        [&desc](::Value::Member const& v)
    {
            auto const& obj = v.value;
            std::string typeStr = obj["type"].GetString();
            Value::Type type;
            if(typeStr=="STRING")
                type = Value::STRING;
            else if(typeStr=="DOUBLE")
                type = Value::DOUBLE;
            else
                type = Value::EMPTY;

            DataSeriesInfo::Properties props = obj["properties"].GetInt();
            std::string misc = obj["misc"].GetString();
            double min = 0.0;
            double max = 0.0;
            if(obj["min"].IsDouble())
                min = obj["min"].GetDouble();
            if(obj["max"].IsDouble())
                max = obj["max"].GetDouble();

            desc.addDataSeries(v.name.GetString(), DataSeriesInfo(type, props, misc, min, max));

    });

    return std::unique_ptr<DescriptionMessage>(new DescriptionMessage(sender, desc));
}

std::unique_ptr<Message> JSONPresentation::decode(ByteVector const& bytes)
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

    if(msgtype == DataMessage::IDENTIFIER)
        return decodeDataMessage(document, sender);
    else if(msgtype == DescriptionMessage::IDENTIFIER)
        return decodeDescriptionMessage(document, sender);
    else
        return std::unique_ptr<Message>(new Message(sender, msgtype));
}

}
