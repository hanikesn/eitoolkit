#include "EIProtobufPresentation.h"
#include "EIDataMessage.h"
#include "EIDescriptionMessage.h"
#include "EIDiscoveryMessage.h"

#include "EIMessage.pb.h"

namespace EI
{

// MSVC gets link errors
#ifndef _MSC_VER
const Byte ProtobufPresentation::IDENTIFIER;
#endif


class ProtobufPresentation::ProtobufPresentationImpl {

};

ProtobufPresentation::ProtobufPresentation(const StringMap &options)
    : pimpl(new ProtobufPresentationImpl)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
}

ProtobufPresentation::~ProtobufPresentation()
{
    google::protobuf::ShutdownProtobufLibrary();
    delete pimpl;
}

Byte ProtobufPresentation::getIdentifier()
{
    return IDENTIFIER;
}

void ProtobufPresentation::encode(const Message &msg, ByteVector &out_buffer)
{
    Protobuf::Message tmp;
    tmp.set_sender(msg.getSender());
    tmp.set_msgtype(msg.getMsgType());

    auto size = out_buffer.size();
    auto bytesize = tmp.ByteSize();

    bool res = tmp.SerializeToArray(out_buffer.data()+size, out_buffer.size()-size);
    assert(res);
}

static std::unique_ptr<DataMessage> decodeDataMessage(Protobuf::Message const& msg)
{
    return 0;
}

static std::unique_ptr<DescriptionMessage> decodeDescriptionMessage(Protobuf::Message const& msg)
{
    return 0;
}

std::unique_ptr<Message> ProtobufPresentation::decode(const ByteVector &in_buffer)
{
    Protobuf::Message msg;
    if(!msg.ParseFromArray(in_buffer.data(), in_buffer.size()))
        throw std::exception();

    auto const& sender = msg.sender();
    auto const& msgtype = msg.msgtype();

    /*if(msgtype == DataMessage::IDENTIFIER)
        return decodeDataMessage(msg);
    else if(msgtype == DescriptionMessage::IDENTIFIER)
        return decodeDescriptionMessage(msg);
    else if(msgtype == DiscoveryMessage::IDENTIFIER)
        return std::unique_ptr<DiscoveryMessage>(new DiscoveryMessage(sender));
    else*/
        return std::unique_ptr<Message>(new Message(sender, msgtype));
}

}
