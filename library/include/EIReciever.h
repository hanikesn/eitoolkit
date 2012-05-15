#ifndef EIReciever_H__
#define EIReciever_H__

#include "EITransport.h"
#include "EIPresentation.h"

#include <map>
#include <string>

namespace EI {

class DataObserver;
class ControlObserver;

class Reciever
{
public:
    /// Erstellt einen UPD Sender mit JSON Darstellung
    /// Options: z.B. Name = asd etc.
    Reciever();
    Reciever(std::map<std::string, std::string> options, Transport&);
    Reciever(std::map<std::string, std::string> options, Transport&, Presentation&);
    ~Reciever();

    void sendDiscover();

    void addReciever(DataObserver*);
    void removeReciever(DataObserver*);

    void addReciever(ControlObserver*);
    void removeReciever(ControlObserver*);
private:
    // Disable copying
    Reciever(const Reciever &);
    Reciever &operator=(const Reciever &);
};

}

#endif
