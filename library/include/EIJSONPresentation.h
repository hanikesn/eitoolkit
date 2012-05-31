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
    JSONPresentation(std::map<std::string, std::string> const& options);
    ~JSONPresentation();

    void encode(Message const& msg, std::vector<Byte> & out_buffer);
    std::shared_ptr<Message> decode(std::vector<Byte> const& in_buffer);

private:
    class JSONPresentationImpl;
    JSONPresentationImpl* const pimpl;
};

}

#endif

