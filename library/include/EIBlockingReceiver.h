#ifndef EIBlockingReceiver_H
#define EIBlockingReceiver_H

#include "EIPrerequisites.h"
#include "EITransport.h"
#include "EIPresentation.h"
#include "EIDataMessage.h"

#include <map>
#include <string>

namespace EI
{

class EITOOLKIT_EXPORT BlockingReceiver
{
public:
    BlockingReceiver(StringMap const& options);
    BlockingReceiver(StringMap const& options, Transport& transport);
    BlockingReceiver(StringMap const& options, Transport& transport, Presentation& presentation);
    ~BlockingReceiver();

    std::vector<DataMessage> getMessages();
    int hasMessages();
    void waitForMessages(int milliseconds);

private:
    // Disable copying
    BlockingReceiver(const BlockingReceiver &);
    BlockingReceiver &operator=(const BlockingReceiver &);
private:
    class BlockingReceiverImpl;
    BlockingReceiverImpl* pimpl;
};

}

#endif
