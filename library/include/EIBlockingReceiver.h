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

/**
 * @brief A synchronous wrapper for the Receiver class.
 *
 * This class wraps a receiver so that it can be used without the usage of multithreading.
 */
class EITOOLKIT_EXPORT BlockingReceiver
{
public:
    /**
     * @brief Constructs a BlockingReceiver object.
     * @details @copydetails Receiver::Receiver(StringMap const& options)
     */
    BlockingReceiver(StringMap const& options);
    /**
     * @brief Constructs a BlockingReceiver object.
     * @details @copydetails Receiver::Receiver(StringMap const& options, Transport& transport)
     */
    BlockingReceiver(StringMap const& options, Transport& transport);
    /**
     * @brief Constructs a BlockingReceiver object.
     * @details @copydetails Receiver::Receiver(StringMap const& options, Transport& transport, Presentation& presentation)
     */
    BlockingReceiver(StringMap const& options, Transport& transport, Presentation& presentation);
    ~BlockingReceiver();

    /**
     * @brief Get a vector of the messages received since the last time getMessages() was called.
     */
    std::vector<DataMessage> getMessages();
    /**
     * @brief Returns the number of messages received since the last time getMessages() was called.
     * @return
     */
    int hasMessages();
    /**
     * @brief Wait until a message arrives.
     * @param milliseconds The timeout in milliseconds after the method will return regardles wether message were received.
     */
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
