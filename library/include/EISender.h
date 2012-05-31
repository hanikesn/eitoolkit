#ifndef EISender_H__
#define EISender_H__

#include "EIPrerequisites.h"
#include "EITransport.h"
#include "EIPresentation.h"
#include "EIMessage.h"
#include "EIDescription.h"

#include <map>
#include <string>

namespace EI
{

class EITOOLKIT_EXPORT Sender
{
public:
    Sender(Description const&, std::map<std::string, std::string> const& options);
    Sender(Description const&, std::map<std::string, std::string> const& options, Transport& transport, Presentation& presentation);
    ~Sender();

    void sendMessage(const Message& msg);
private:
    // Disable copying
    Sender(const Sender &);
    Sender &operator=(const Sender &);
private:
    class SenderImpl;
    SenderImpl* const pimpl;
};

}

#endif
