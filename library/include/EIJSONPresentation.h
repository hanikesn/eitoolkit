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

    void encode(Packet const&, std::vector<Byte> &);
    std::shared_ptr<Packet> decode(std::vector<Byte> const&);

private:
    class JSONPresentationImpl;
    JSONPresentationImpl* const pimpl;
};

}

#endif

