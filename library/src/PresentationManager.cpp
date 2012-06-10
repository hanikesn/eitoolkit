#include "PresentationManager.h"

namespace EI
{

PresentationManager::PresentationManager(StringMap const& options, Presentation* pres)
    : pres(pres),
      jsonPresentation(options)
#ifdef HAVE_PROTOBUF
      ,protobufPresentation(options)
#endif
{
    auto it = options.find("useProtobuf");
    useProtobuf = it != options.end();
}

std::unique_ptr<Message> PresentationManager::decode(const ByteVector &in_buffer)
{
    if(in_buffer.empty())
        throw std::exception();

    ByteVector buffer(in_buffer.begin()+1, in_buffer.end());

    switch(in_buffer.front())
    {
    case JSONPresentation::IDENTIFIER:
        return jsonPresentation.decode(buffer);
        break;
#ifdef HAVE_PROTOBUF
    case ProtobufPresentation::IDENTIFIER:
        return protobufPresentation.decode(buffer);
        break;
#endif
    default:
        throw std::exception();
    }

    return 0;
}

void PresentationManager::encode(const Message &msg, ByteVector &out_buffer)
{
    if(pres) {
        out_buffer.push_back(pres->getIdentifier());
        return pres->encode(msg, out_buffer);
    }

#ifdef HAVE_PROTOBUF
    if(useProtobuf) {
        out_buffer.push_back(ProtobufPresentation::IDENTIFIER);
        return protobufPresentation.encode(msg, out_buffer);
    }
#endif

    out_buffer.push_back(JSONPresentation::IDENTIFIER);
    return jsonPresentation.encode(msg, out_buffer);
}

}
