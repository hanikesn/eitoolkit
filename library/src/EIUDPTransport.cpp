#include "EIUDPTransport.h"

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include "EIThread.h"
#include <boost/asio/ip/udp.hpp>
#include <boost/system/system_error.hpp>

namespace EI
{

namespace ba = boost::asio;
namespace bs = boost;

class Worker
{
public:
    Worker(ba::ip::udp::socket& socket, Transport::Channel type, PacketListener* ob)
        : ob(ob), socket(socket), recv_buffer(8000), type(type)
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
            out_buffer.assign(recv_buffer.begin(), recv_buffer.begin() + bytes_transferred);
            ob->onPacket(type, out_buffer);
            start_receive();
        }
    }

private:
    PacketListener* ob;
    ba::ip::udp::socket& socket;
    ByteVector recv_buffer;
    ByteVector out_buffer;
    Transport::Channel type;
};

class UDPTransport::UDPTransportImpl : public PacketListener
{
public:
    UDPTransportImpl(StringMap const& options);
    ~UDPTransportImpl();

    void sendPacket(Transport::Channel, ByteVector const&);
    void addPacketListener(Transport::Channel, PacketListener*);
    void removePacketListener(PacketListener*);

    virtual void onPacket(Transport::Channel, ByteVector const&);
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

UDPTransport::UDPTransport(StringMap const& options )
    : pimpl(new UDPTransportImpl(options))
{}

UDPTransport::~UDPTransport()
{
    delete pimpl;
}

void UDPTransport::sendPacket(Channel type, ByteVector const& packet) throw (EI::Exception)
{
    pimpl->sendPacket(type, packet);
}
    
void UDPTransport::addPacketListener(Channel type, PacketListener* ob)
{
    pimpl->addPacketListener(type, ob);
}

void UDPTransport::removePacketListener(PacketListener* ob)
{
    pimpl->removePacketListener(ob);
}

#ifdef _MSC_VER
#pragma warning(push)
// VC warns uns about the use of this in the intializer list. But this is safe because we only
// store the pointer in the Worker classes and don't access anything else.
#pragma warning(disable: 4355)
#endif

UDPTransport::UDPTransportImpl::UDPTransportImpl(StringMap const&)
    : dataSocket(io_service, ba::ip::udp::v4()),
      controlSocket(io_service, ba::ip::udp::v4()),
      dataEndpoint(ba::ip::address_v4::broadcast(), 31337),
      controlEndpoint(ba::ip::address_v4::broadcast(), 31338),
      dataWorker(dataSocket, Transport::DATA, this),
      controlWorker(controlSocket, Transport::COMMUNICATION, this)

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
#ifdef _MSC_VER
#pragma warning(pop)
#endif

UDPTransport::UDPTransportImpl::~UDPTransportImpl()
{
    if(thread.joinable())
        thread.join();
}

void UDPTransport::UDPTransportImpl::addPacketListener(Transport::Channel type, PacketListener* ob)
{
    if(!ob)
        return;
    Thread::lock_guard lock(mutex);

    if(type == Transport::ALL || type == Transport::DATA)
        dataListeners.push_back(ob);

    if(type == Transport::ALL || type == Transport::COMMUNICATION)
        controlListeners.push_back(ob);

    if(!thread.joinable()) {
        thread = Thread::thread([this](){this->io_service.run();});
    }
}

void UDPTransport::UDPTransportImpl::removePacketListener(PacketListener* ob)
{
    Thread::lock_guard lock(mutex);

    controlListeners.erase(std::remove(std::begin(controlListeners), std::end(controlListeners), ob), std::end(controlListeners));
    dataListeners.erase(std::remove(std::begin(dataListeners), std::end(dataListeners), ob), std::end(dataListeners));
    if(dataListeners.empty() && controlListeners.empty()) {
        io_service.stop();
        if(thread.joinable())
            thread.join();
    }
}

void UDPTransport::UDPTransportImpl::onPacket(Transport::Channel type, ByteVector const& p)
{
    Thread::lock_guard lock(mutex);

    auto& observers = type == Transport::DATA ? dataListeners : controlListeners;

    std::for_each(std::begin(observers), std::end(observers),
        [type, &p](PacketListener* ob)
        {
            ob->onPacket(type, p);
        });
}

void UDPTransport::UDPTransportImpl::sendPacket(Transport::Channel type, ByteVector const& p)
{
    try {
        switch(type)
        {
        case Transport::DATA:
            dataSocket.send_to(boost::asio::buffer(p), dataEndpoint);
            break;
        case Transport::COMMUNICATION:
            controlSocket.send_to(boost::asio::buffer(p), controlEndpoint);
            break;
        case Transport::ALL:
            break;
        }
    } catch(boost::system::system_error const& e) {
        std::cerr << e.what() << "\n";
        throw EI_EXCEPTION("Error while sending.");
    }
}

}
