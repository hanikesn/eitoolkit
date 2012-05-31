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

class EITOOLKIT_EXPORT BlockingReceiver
{
public:
    BlockingReceiver(std::map<std::string, std::string> const& options);
    BlockingReceiver(std::map<std::string, std::string> const& options, Transport& transport);
    BlockingReceiver(std::map<std::string, std::string> const& options, Transport& transport, Presentation& presentation);
    ~BlockingReceiver();

    std::vector<DataPacket> getPackets();
    int hasPackets();
    void waitForPackets(int milliseconds);

private:
    class BlockingReceiverImpl;
    BlockingReceiverImpl* pimpl;
};

}

#endif
