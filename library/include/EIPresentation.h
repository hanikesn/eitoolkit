#ifndef EIPresentation_H__
#define EIPresentation_H__

#include "EIPrerequisites.h"
#include "EIMessage.h"

#include <vector>
#include <memory>

namespace EI
{

/**
 * @brief Abstract base class for all presentations.
 *
 * Presentations are responsible for the encoding of @ref Message messages.
 *
 * @note All methods should be @ref threadsafe "thread-safe".
 */
class EITOOLKIT_EXPORT Presentation
{
public:
    virtual ~Presentation();
    /**
     * @brief Encodes a message for delivery.
     * @param msg The message to encode.
     * @param out_buffer The buffer where encoded bytes are written into. To save recurring allocations this not a return value.
     */
    virtual void encode(Message const& msg, ByteVector& out_buffer) = 0;

    /**
     * @brief Decodes a message.
     * @param in_buffer The bytes to decode.
     * @return A pointer to the decoded message. Ownership is transfered to the callee.
     */
    virtual std::unique_ptr<Message> decode(ByteVector const& in_buffer) = 0;
};

}

#endif
