#ifndef IEReciever_H__
#define IEReciever_H__

#include "IETransport.h"
#include "IEPresentation.h"

#include <map>
#include <string>

namespace IE {

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
