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
    Worker(ba::ip::udp::socket& socket, Transport::Type type, BytePacketObserver& ob)
        : socket(socket), type(type), ob(ob), recv_buffer(1500)
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
            ob.onBytePacket(type, out_buffer);
            start_receive();
        }
    }

private:
    ba::ip::udp::socket& socket;
    Transport::Type type;
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
    boost::thread thread;
    boost::mutex mutex;
    ba::io_service io_service;
    ba::ip::udp::socket dataSocket;
    ba::ip::udp::socket controlSocket;
    ba::ip::udp::endpoint dataEndpoint;
    ba::ip::udp::endpoint controlEndpoint;

    Worker dataWorker;
    Worker controlWorker;

    std::vector<BytePacketObserver*> dataObservers;
    std::vector<BytePacketObserver*> controlObservers;
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
    : dataSocket(io_service, ba::ip::udp::v4()),
      controlSocket(io_service, ba::ip::udp::v4()),
      dataEndpoint(ba::ip::address_v4::broadcast(), 31337),
      controlEndpoint(ba::ip::address_v4::broadcast(), 31338),
      dataWorker(dataSocket, Transport::DATA, *this),
      controlWorker(controlSocket, Transport::CONTROL, *this)

{   dataSocket.set_option(ba::socket_base::reuse_address(true));
    dataSocket.set_option(ba::socket_base::broadcast(true));
    dataSocket.bind(dataEndpoint);
    dataWorker.start_receive();

    controlSocket.set_option(ba::socket_base::reuse_address(true));
    controlSocket.set_option(ba::socket_base::broadcast(true));
    controlSocket.bind(controlEndpoint);
    controlWorker.start_receive();
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

    if(!thread.joinable()) {
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
    switch(type)
    {
    case Transport::DATA:
        dataSocket.send_to(boost::asio::buffer(p), dataEndpoint);
        break;
    case Transport::CONTROL:
        controlSocket.send_to(boost::asio::buffer(p), controlEndpoint);
        break;
    case Transport::ALL:
        break;
    }
}

}
