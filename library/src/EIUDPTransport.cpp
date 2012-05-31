#include "EIUDPTransport.h"

#include <vector>
#include <memory>
#include <algorithm>
#include "EIThread.h"
#include <boost/asio/ip/udp.hpp>

namespace EI
{

namespace ba = boost::asio;
namespace bs = boost;

class Worker
{
public:
    Worker(ba::ip::udp::socket& socket, Transport::Type type, PacketObserver& ob)
        : socket(socket), type(type), ob(ob), recv_buffer(8000)
    {}

    void start_receive()
    {
        socket.async_receive(ba::buffer(recv_buffer), [this](const bs::system::error_code& error,
                                                 std::size_t bytes_transferred) {
                                  this->handle_receive(error, bytes_transferred);
        });
    }

private:
    void handle_receive(const bs::system::error_code& error,
                        std::size_t bytes_transferred)
    {
        if (!error || error == boost::asio::error::message_size)
        {
            std::vector<Byte> out_buffer(bytes_transferred);
            copy(std::begin(recv_buffer), std::begin(recv_buffer)+bytes_transferred, std::begin(out_buffer));
            ob.onPacket(type, out_buffer);
            start_receive();
        }
    }

private:
    ba::ip::udp::socket& socket;
    Transport::Type type;
    PacketObserver& ob;

    std::vector<Byte> recv_buffer;
};

class UDPTransport::UDPTransportImpl : public PacketObserver
{
public:
    UDPTransportImpl(std::map<std::string, std::string> const& options);
    ~UDPTransportImpl();

    void sendPacket(Transport::Type, std::vector<Byte> const&);
    void addPacketObserver(Transport::Type, PacketObserver&);
    void removePacketObserver(PacketObserver&);

    virtual void onPacket(Transport::Type, std::vector<Byte> const&);
private:
    Thread::thread thread;
    Thread::mutex mutex;
    ba::io_service io_service;
    ba::ip::udp::socket dataSocket;
    ba::ip::udp::socket controlSocket;
    ba::ip::udp::endpoint dataEndpoint;
    ba::ip::udp::endpoint controlEndpoint;

    Worker dataWorker;
    Worker controlWorker;

    std::vector<PacketObserver*> dataObservers;
    std::vector<PacketObserver*> controlObservers;
};

UDPTransport::UDPTransport(std::map<std::string, std::string> const& options )
    : pimpl(new UDPTransportImpl(options))
{}

UDPTransport::~UDPTransport()
{
    delete pimpl;
}

void UDPTransport::sendPacket(Type type, std::vector<Byte> const& packet)
{
    pimpl->sendPacket(type, packet);
}
    
void UDPTransport::addPacketObserver(Type type, PacketObserver& ob)
{
    pimpl->addPacketObserver(type, ob);
}

void UDPTransport::removePacketObserver(PacketObserver& ob)
{
    pimpl->removePacketObserver(ob);
}

UDPTransport::UDPTransportImpl::UDPTransportImpl(std::map<std::string, std::string> const&)
    : dataSocket(io_service, ba::ip::udp::v4()),
      controlSocket(io_service, ba::ip::udp::v4()),
      dataEndpoint(ba::ip::address_v4::broadcast(), 31337),
      controlEndpoint(ba::ip::address_v4::broadcast(), 31338),
      dataWorker(dataSocket, Transport::DATA, *this),
      controlWorker(controlSocket, Transport::CONTROL, *this)

{   
    dataSocket.set_option(ba::socket_base::reuse_address(true));
    dataSocket.set_option(ba::socket_base::broadcast(true));
    dataSocket.bind(ba::ip::udp::endpoint(ba::ip::address_v4::any(), 31337));
    dataWorker.start_receive();

    controlSocket.set_option(ba::socket_base::reuse_address(true));
    controlSocket.set_option(ba::socket_base::broadcast(true));
    controlSocket.bind(ba::ip::udp::endpoint(ba::ip::address_v4::any(), 31338));
    controlWorker.start_receive();
}

UDPTransport::UDPTransportImpl::~UDPTransportImpl()
{
    if(thread.joinable())
        thread.join();
}

void UDPTransport::UDPTransportImpl::addPacketObserver(Transport::Type type, PacketObserver& ob)
{
    Thread::lock_guard lock(mutex);

    if(type == Transport::ALL || type == Transport::DATA)
        dataObservers.push_back(&ob);

    if(type == Transport::ALL || type == Transport::CONTROL)
        controlObservers.push_back(&ob);

    if(!thread.joinable()) {
        thread = Thread::thread([this](){this->io_service.run();});
    }
}

void UDPTransport::UDPTransportImpl::removePacketObserver(PacketObserver& ob)
{
    Thread::lock_guard lock(mutex);

    controlObservers.erase(std::remove(std::begin(controlObservers), std::end(controlObservers), &ob), std::end(controlObservers));
    dataObservers.erase(std::remove(std::begin(dataObservers), std::end(dataObservers), &ob), std::end(dataObservers));
    if(dataObservers.empty() && controlObservers.empty()) {
        io_service.stop();
        if(thread.joinable())
            thread.join();
    }
}

void UDPTransport::UDPTransportImpl::onPacket(Transport::Type type, std::vector<Byte> const& p)
{
    Thread::lock_guard lock(mutex);

    auto& observers = type == Transport::DATA ? dataObservers : controlObservers;

    std::for_each(std::begin(observers), std::end(observers),
        [type, &p](PacketObserver* ob)
        {
            ob->onPacket(type, p);
        });
}

void UDPTransport::UDPTransportImpl::sendPacket(Transport::Type type, std::vector<Byte> const& p)
{
    switch(type)
    {
    case Transport::DATA:
        if(dataSocket.send_to(boost::asio::buffer(p), dataEndpoint) != p.size()) {
            throw std::exception();
        }
        break;
    case Transport::CONTROL:
        if(controlSocket.send_to(boost::asio::buffer(p), controlEndpoint) != p.size()) {
            throw std::exception();
        }
        break;
    case Transport::ALL:
        break;
    }
}

}
