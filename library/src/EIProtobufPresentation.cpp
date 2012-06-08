#include "EIProtobufPresentation.h"

#include "EIMessage.pb.h"

namespace EI
{

const Byte ProtobufPresentation::IDENTIFIER;

class ProtobufPresentation::ProtobufPresentationImpl {

};

ProtobufPresentation::ProtobufPresentation(const StringMap &options)
    : pimpl(new ProtobufPresentationImpl)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
}

ProtobufPresentation::~ProtobufPresentation()
{
    delete pimpl;
}

Byte ProtobufPresentation::getIdentifier()
{
    return IDENTIFIER;
}

void ProtobufPresentation::encode(const Message &msg, ByteVector &out_buffer)
{

}

std::unique_ptr<Message> ProtobufPresentation::decode(const ByteVector &in_buffer)
{
    return 0;
}

}
