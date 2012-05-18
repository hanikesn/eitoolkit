namespace EI
{
typedef char Byte;

class BytePacketObserver;
class ControlObserver;
class DataObserver;
class Packet;
class Receiver;
class Sender;
class Transport;
class UDPTransport;

class Packet
{
};

class Presentation
{
public:
    virtual ~Presentation();
    virtual std::vector<Byte> encode(Packet) = 0;
    virtual Packet decode(std::vector<Byte>) = 0;
};

class DataObserver
{
public:
    virtual ~DataObserver() {};
    virtual void onPacket(Packet) = 0;
};

class ControlObserver
{
public:
    virtual ~ControlObserver() {};
    virtual void onPacket(Packet) = 0;
};

class Receiver
{
public:
    Receiver(std::map<std::string, std::string> options);
    Receiver(std::map<std::string, std::string> options, Transport&);
    Receiver(std::map<std::string, std::string> options, Transport&, Presentation&);
    ~Receiver();

    void sendDiscover();

    void addDataListener(DataObserver*);
    void removeDataListener(DataObserver*);

    void addControlListener(ControlObserver*);
    void removeControlListener(ControlObserver*);
};

class Sender
{
public:
    Sender(std::map<std::string, std::string> options);
    Sender(std::map<std::string, std::string> options, Transport&, Presentation&);
    ~Sender();

    void sendPacket(Packet);
};

class Transport
{
public:
    enum Type {ALL, DATA, CONTROL};

    virtual ~Transport();

    virtual void sendBytePacket(Type, std::vector<Byte>) = 0;
    virtual void addBytePacketObserver(Type, BytePacketObserver*) = 0;
    virtual void removeBytePacketObserver(BytePacketObserver*) = 0;
};

class BytePacketObserver
{
public:
    virtual ~BytePacketObserver() {};
    virtual void onBytePacket(Transport::Type, std::vector<Byte>) = 0;
};

}
