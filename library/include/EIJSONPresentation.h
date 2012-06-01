#ifndef EIJSONPresentation_H
#define EIJSONPresentation_H

#include <EIPrerequisites.h>
#include <EIPresentation.h>

#include <map>
#include <string>

namespace EI
{

class EITOOLKIT_EXPORT JSONPresentation : public Presentation
{
public:
    JSONPresentation(StringMap const& options);
    ~JSONPresentation();

    void encode(Message const& msg, ByteVector & out_buffer);
    std::shared_ptr<Message> decode(ByteVector const& in_buffer);

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

