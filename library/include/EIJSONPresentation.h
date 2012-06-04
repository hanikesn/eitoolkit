#ifndef EIJSONPresentation_H
#define EIJSONPresentation_H

#include <EIPrerequisites.h>
#include <EIPresentation.h>

#include <map>
#include <string>

namespace EI
{

/**
 * @brief A Presentation for JSON encoding and decoding.
 *
 * @nocopy
 */
class EITOOLKIT_EXPORT JSONPresentation : public Presentation
{
public:
    /**
     * @brief Constructs a JSONPresentation object.
     * @param options The options used. Currently none are supported.
     */
    JSONPresentation(StringMap const& options);
    ~JSONPresentation();

    void encode(Message const& msg, ByteVector & out_buffer);
    std::unique_ptr<Message> decode(ByteVector const& in_buffer);

private:
    // Disable copying
    JSONPresentation(const JSONPresentation &);
    JSONPresentation &operator=(const JSONPresentation &);
private:
    class JSONPresentationImpl;
    JSONPresentationImpl* const pimpl;
};

}

#endif

