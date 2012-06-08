#ifndef EIJSONPresentation_H
#define EIProtobufPresentation_H

#include <EIPrerequisites.h>
#include <EIPresentation.h>

#include <map>
#include <string>

namespace EI
{

/**
 * @brief A Presentation for Protobuf encoding and decoding.
 *
 * @nocopy
 */
class EITOOLKIT_EXPORT ProtobufPresentation : public Presentation
{
public:
    /**
     * @brief Constructs a ProtobufPresentation object.
     * @param options The options used. Currently none are supported.
     */
    ProtobufPresentation(StringMap const& options);
    ~ProtobufPresentation();

    void encode(Message const& msg, ByteVector & out_buffer);
    std::unique_ptr<Message> decode(ByteVector const& in_buffer);

private:
    // Disable copying
    ProtobufPresentation(const ProtobufPresentation &);
    ProtobufPresentation &operator=(const ProtobufPresentation &);
private:
    class ProtobufPresentationImpl;
    ProtobufPresentationImpl* const pimpl;
};

}

#endif

