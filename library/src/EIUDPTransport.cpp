#include "EIUDPTransport.h"

#include <vector>
#include <memory>
#include <boost/thread.hpp>
#include <boost/asio.hpp>

namespace EI
{

class Worker
{
public:
    Worker(boost::asio::io_service&);

    boost::asio::ip::udp::socket socket;
};

Worker::Worker(boost::asio::io_service& io_service)
    : socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 31337))
{
}


class UDPTransport::UDPTransportImpl : public BytePacketObserver
{
public:
    UDPTransportImpl(std::map<std::string, std::string> options);
    ~UDPTransportImpl();

    void sendBytePacket(Transport::Type, std::vector<Byte>);
    void addBytePacketObserver(Transport::Type, BytePacketObserver*);
    void removeBytePacketObserver(BytePacketObserver*);

    virtual void onBytePacket(Transport::Type, std::vector<Byte>);
private:
    std::unique_ptr<Worker> worker;
    boost::thread thread;
    boost::mutex mutex;
    boost::asio::io_service io_service;
    boost::asio::ip::udp::socket socket;

    std::vector<BytePacketObserver*> controlObservers;
    std::vector<BytePacketObserver*> dataObservers;
};

UDPTransport::UDPTransport(std::map<std::string, std::string> options)
    : pimpl(new UDPTransportImpl(options))
{}

UDPTransport::~UDPTransport()
{
    delete pimpl;
}

void UDPTransport::sendBytePacket(Type type, std::vector<Byte> packet)
{
    pimpl->sendBytePacket(type, packet);
}
    
void UDPTransport::addBytePacketObserver(Type type, BytePacketObserver* ob)
{
    pimpl->addBytePacketObserver(type, ob);
}

void UDPTransport::removeBytePacketObserver(BytePacketObserver* ob)
{
    pimpl->removeBytePacketObserver(ob);
}

UDPTransport::UDPTransportImpl::UDPTransportImpl(std::map<std::string, std::string> options)
    : socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 31337))
{
    socket.set_option(boost::asio::socket_base::broadcast(true));
}

UDPTransport::UDPTransportImpl::~UDPTransportImpl()
{
    thread.join();
}

void UDPTransport::UDPTransportImpl::addBytePacketObserver(Transport::Type, BytePacketObserver*)
{
    boost::lock_guard<boost::mutex> lock(mutex);
    if(!worker) {
        worker.reset(new Worker(io_service));
        thread = boost::thread([this](){this->io_service.run();});
    }
}

void UDPTransport::UDPTransportImpl::removeBytePacketObserver(BytePacketObserver* ob)
{
    boost::lock_guard<boost::mutex> lock(mutex);
    std::remove(std::begin(controlObservers), std::end(controlObservers), ob);
    std::remove(std::begin(dataObservers), std::end(dataObservers), ob);
    if(dataObservers.empty() && controlObservers.empty()) {
        io_service.stop();
        thread.join();
        worker.release();
    }
}

void UDPTransport::UDPTransportImpl::onBytePacket(Transport::Type type, std::vector<Byte> p)
{
    boost::lock_guard<boost::mutex> lock(mutex);

    auto& observers = type == Transport::DATA ? dataObservers : controlObservers;

    std::for_each(std::begin(observers), std::end(observers),
        [type, &p](BytePacketObserver* ob)
        {
            ob->onBytePacket(type, p);
        });
}

void UDPTransport::UDPTransportImpl::sendBytePacket(Transport::Type type, std::vector<Byte> p)
{
    socket.send(boost::asio::buffer(p));
}

}