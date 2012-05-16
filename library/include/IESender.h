#ifndef IESender_H__
#define IESender_H__

#include "IETransport.h"
#include "IEPresentation.h"
#include "IEPacket.h"

#include <map>
#include <string>

namespace IE {

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
