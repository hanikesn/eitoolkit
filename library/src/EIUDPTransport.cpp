#include "EIUDPTransport.h"

#include <vector>
#include <memory>
#include <boost/array.hpp>
#include <boost/thread.hpp>
#include <boost/asio/ip/udp.hpp>

namespace EI
{

namespace ba = boost::asio;
namespace bs = boost;

class Worker
{
public:
    Worker(ba::ip::udp::socket& socket, BytePacketObserver& ob)
        : socket(socket), ob(ob), recv_buffer(1500)
    {
        start_receive();
    }

private:
    void start_receive()
    {
        socket.async_receive(ba::buffer(recv_buffer), [this](const bs::system::error_code& error,
                                                 std::size_t bytes_transferred) {
                                  this->handle_receive(error, bytes_transferred);
        });
    }

    void handle_receive(const bs::system::error_code& error,
                        std::size_t bytes_transferred)
    {
        if (!error || error == boost::asio::error::message_size)
        {
            ob.onBytePacket(Transport::DATA, recv_buffer);
            start_receive();
        }
    }

private:
    ba::ip::udp::socket& socket;
    BytePacketObserver& ob;

    std::vector<Byte> recv_buffer;
};

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
    ba::io_service io_service;
    ba::ip::udp::socket socket;
    ba::ip::udp::endpoint endpoint;

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
    : socket(io_service, ba::ip::udp::v4()) , endpoint(ba::ip::address_v4::broadcast(), 31337)
{
    socket.set_option(ba::socket_base::reuse_address(true));
    socket.set_option(ba::socket_base::broadcast(true));
    socket.bind(ba::ip::udp::endpoint(boost::asio::ip::address_v4::broadcast(), 31337));
}

UDPTransport::UDPTransportImpl::~UDPTransportImpl()
{
    thread.join();
}

void UDPTransport::UDPTransportImpl::addBytePacketObserver(Transport::Type type, BytePacketObserver* ob)
{
    boost::lock_guard<boost::mutex> lock(mutex);

    if(type == Transport::ALL || Transport::DATA)
        dataObservers.push_back(ob);

    if(type == Transport::ALL || Transport::CONTROL)
        controlObservers.push_back(ob);

    if(!worker) {
        worker.reset(new Worker(socket, *this));
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
    socket.send_to(boost::asio::buffer(p), endpoint);
}

}
