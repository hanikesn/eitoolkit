#ifndef EISender_H__
#define EISender_H__

#include "EITransport.h"
#include "EIPresentation.h"
#include "EIPacket.h"

#include <map>
#include <string>

namespace EI {

class Sender
{
public:
    /// Erstellt einen UPD Sender mit JSON Darstellung
    /// Options: z.B. Name = asd etc.
    Sender(std::map<std::string, std::string> options);
    Sender(std::map<std::string, std::string> options, Transport&, Presentation&);
    ~Sender();

    void sendPacket(Packet);
private:
    // Disable copying
    Sender(const Sender &);
    Sender &operator=(const Sender &);
};

}

#endif
