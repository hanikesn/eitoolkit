#include "EIBlockingReceiver.h"
#include "EIReceiver.h"
#include "EIThread.h"

namespace EI
{

class BlockingReceiver::BlockingReceiverImpl : public DataListener
{
public:
    BlockingReceiverImpl(StringMap const& options) : receiver(options) {}
    BlockingReceiverImpl(StringMap const& options, Transport& transport) : receiver(options, transport) {}
    BlockingReceiverImpl(StringMap const& options, Transport& transport, Presentation& presentation) : receiver(options, transport, presentation) {}

    void onMessage(DataMessage);

    std::vector<DataMessage> buffer;
    Receiver receiver;
    Thread::mutex mutex;
    Thread::condition_variable buffer_not_empty;
};

BlockingReceiver::BlockingReceiver(StringMap const& options)
    : pimpl(new BlockingReceiverImpl(options))
{
    pimpl->receiver.addDataListener(pimpl);
}

BlockingReceiver::BlockingReceiver(StringMap const& options, Transport& transport)
    : pimpl(new BlockingReceiverImpl(options, transport))
{
    pimpl->receiver.addDataListener(pimpl);
}

BlockingReceiver::BlockingReceiver(StringMap const& options, Transport& transport, Presentation& presentation)
    : pimpl(new BlockingReceiverImpl(options, transport, presentation))
{
    pimpl->receiver.addDataListener(pimpl);
}

BlockingReceiver::~BlockingReceiver()
{
    pimpl->receiver.removeDataListener(pimpl);
    delete pimpl;
}

void BlockingReceiver::BlockingReceiverImpl::onMessage(DataMessage msg)
{
    {
        Thread::lock_guard lock(mutex);
        buffer.push_back(std::move(msg));
    }

    buffer_not_empty.notify_one();
}

void BlockingReceiver::waitForMessages(int milliseconds)
{
    Thread::unique_lock lock(pimpl->mutex);

    while(pimpl->buffer.empty())
    {
        // unlock and wait
        #ifdef HAVE_THREAD_H
            pimpl->buffer_not_empty.wait_for(lock, std::chrono::milliseconds(milliseconds));
        #else
            pimpl->buffer_not_empty.timed_wait(lock, boost::posix_time::milliseconds(milliseconds));
        #endif
    }
}

int BlockingReceiver::hasMessages()
{
    Thread::lock_guard lock(pimpl->mutex);
    return pimpl->buffer.size();
}

std::vector<DataMessage> BlockingReceiver::getMessages()
{
    Thread::lock_guard lock(pimpl->mutex);

    auto tmp = std::move(pimpl->buffer);

    pimpl->buffer = std::vector<DataMessage>();

    return std::move(tmp);
}

}
