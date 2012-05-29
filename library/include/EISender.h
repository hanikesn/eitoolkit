#ifndef EISender_H__
#define EISender_H__

#include "EIPrerequisites.h"
#include "EITransport.h"
#include "EIPresentation.h"
#include "EIPacket.h"
#include "EIDescription.h"

#include <map>
#include <string>

namespace EI
{

class EITOOLKIT_EXPORT Sender
{
public:
    /// Erstellt einen UPD Sender mit JSON Darstellung
    /// Options: z.B. Name = asd etc.
    Sender(Description const&, std::map<std::string, std::string> const& options);
    Sender(Description const&, std::map<std::string, std::string> const& options, Transport&, Presentation&);
    ~Sender();

    void sendPacket(const Packet&);
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
