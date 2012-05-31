#include "EIBlockingReceiver.h"
#include "EIReceiver.h"
#include "EIThread.h"

namespace EI
{

class BlockingReceiver::BlockingReceiverImpl : public DataObserver
{
public:
    BlockingReceiverImpl(std::map<std::string, std::string> const& options) : receiver(options) {}
    BlockingReceiverImpl(std::map<std::string, std::string> const& options, Transport& transport) : receiver(options, transport) {}
    BlockingReceiverImpl(std::map<std::string, std::string> const& options, Transport& transport, Presentation& presentation) : receiver(options, transport, presentation) {}

    void onPacket(const DataMessage &);

    std::vector<DataMessage> buffer;
    Receiver receiver;
    Thread::mutex mutex;
    Thread::condition_variable buffer_not_empty;
};

BlockingReceiver::BlockingReceiver(std::map<std::string, std::string> const& options)
    : pimpl(new BlockingReceiverImpl(options))
{
}

BlockingReceiver::BlockingReceiver(std::map<std::string, std::string> const& options, Transport& transport)
    : pimpl(new BlockingReceiverImpl(options, transport))
{
}

BlockingReceiver::BlockingReceiver(std::map<std::string, std::string> const& options, Transport& transport, Presentation& presentation)
    : pimpl(new BlockingReceiverImpl(options, transport, presentation))
{
}

BlockingReceiver::~BlockingReceiver()
{
    delete pimpl;
}

void BlockingReceiver::BlockingReceiverImpl::onPacket(const DataMessage & packet)
{
    {
        Thread::lock_guard lock(mutex);
        buffer.push_back(packet);
    }

    buffer_not_empty.notify_one();
}

void BlockingReceiver::waitForPackets(int milliseconds)
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

int BlockingReceiver::hasPackets()
{
    Thread::lock_guard lock(pimpl->mutex);
    return pimpl->buffer.size();
}

std::vector<DataMessage> BlockingReceiver::getMessages()
{
    Thread::lock_guard lock(pimpl->mutex);

    auto tmp = std::move(pimpl->buffer);

    pimpl->buffer.clear();

    return std::move(tmp);
}

}
