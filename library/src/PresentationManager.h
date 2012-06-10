#ifndef PresentationManager_H
#define PresentationManager_H

#include "EIJSONPresentation.h"

#ifdef HAVE_PROTOBUF
    #include "EIProtobufPresentation.h"
#endif

namespace EI
{

class PresentationManager
{
public:
    PresentationManager(StringMap const& options, Presentation*);

    void encode(Message const& msg, ByteVector& out_buffer);
    std::unique_ptr<Message> decode(ByteVector const& in_buffer);

private:
    Presentation* pres;

    JSONPresentation jsonPresentation;
    bool useProtobuf;
#ifdef HAVE_PROTOBUF
    ProtobufPresentation protobufPresentation;
#endif
};

}

#endif
