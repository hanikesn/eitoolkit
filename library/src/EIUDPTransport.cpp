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
    Worker(ba::ip::udp::socket& socket, Transport::Type type, PacketListener& ob)
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
    PacketListener& ob;

    std::vector<Byte> recv_buffer;
};

class UDPTransport::UDPTransportImpl : public PacketListener
{
public:
    UDPTransportImpl(std::map<std::string, std::string> const& options);
    ~UDPTransportImpl();

    void sendPacket(Transport::Type, std::vector<Byte> const&);
    void addPacketListener(Transport::Type, PacketListener&);
    void removePacketListener(PacketListener&);

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

    std::vector<PacketListener*> dataListeners;
    std::vector<PacketListener*> controlListeners;
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
    
void UDPTransport::addPacketListener(Type type, PacketListener& ob)
{
    pimpl->addPacketListener(type, ob);
}

void UDPTransport::removePacketListener(PacketListener& ob)
{
    pimpl->removePacketListener(ob);
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

void UDPTransport::UDPTransportImpl::addPacketListener(Transport::Type type, PacketListener& ob)
{
    Thread::lock_guard lock(mutex);

    if(type == Transport::ALL || type == Transport::DATA)
        dataListeners.push_back(&ob);

    if(type == Transport::ALL || type == Transport::CONTROL)
        controlListeners.push_back(&ob);

    if(!thread.joinable()) {
        thread = Thread::thread([this](){this->io_service.run();});
    }
}

void UDPTransport::UDPTransportImpl::removePacketListener(PacketListener& ob)
{
    Thread::lock_guard lock(mutex);

    controlListeners.erase(std::remove(std::begin(controlListeners), std::end(controlListeners), &ob), std::end(controlListeners));
    dataListeners.erase(std::remove(std::begin(dataListeners), std::end(dataListeners), &ob), std::end(dataListeners));
    if(dataListeners.empty() && controlListeners.empty()) {
        io_service.stop();
        if(thread.joinable())
            thread.join();
    }
}

void UDPTransport::UDPTransportImpl::onPacket(Transport::Type type, std::vector<Byte> const& p)
{
    Thread::lock_guard lock(mutex);

    auto& observers = type == Transport::DATA ? dataListeners : controlListeners;

    std::for_each(std::begin(observers), std::end(observers),
        [type, &p](PacketListener* ob)
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
