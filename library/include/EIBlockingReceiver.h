#ifndef EIBlockingReceiver_H
#define EIBlockingReceiver_H

#include "EIPrerequisites.h"
#include "EITransport.h"
#include "EIPresentation.h"
#include "EIDataPacket.h"

#include <map>
#include <string>

namespace EI
{

class BlockingReceiver
{
public:
    BlockingReceiver(std::map<std::string, std::string> const& options);
    BlockingReceiver(std::map<std::string, std::string> const& options, Transport&);
    BlockingReceiver(std::map<std::string, std::string> const& options, Transport&, Presentation&);
    ~BlockingReceiver();

    void waitForPackets(int milliseconds);
    int hasPackets();
    std::vector<DataPacket> getPackets();

private:
    class BlockingReceiverImpl;
    BlockingReceiverImpl* pimpl;
};

}

#endif
