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
public:
    Packet(std::string const& sender, std::string const& msgtype);
    Packet(Packet const& other);
    virtual ~Packet();

    std::string const& getSender() const;
    std::string const& getMsgtype() const;
};

class DataPacket : public Packet
{
public:
    DataPacket(std::string const& name);

    void setString(std::string const&, std::string  const&);
    std::string getString(std::string  const&);

    void setDouble(std::string  const&, double);
    double getDouble(std::string const&);
};

class Presentation
{
public:
    virtual ~Presentation();
    void encode(Packet const&, std::vector<Byte> &) = 0;
};

class DataObserver
{
public:
    virtual ~DataObserver() {}
    virtual void onPacket(DataPacket const&) = 0;
};

class ControlObserver
{
public:
    virtual ~ControlObserver() {}
    virtual void onPacket(Packet const&) = 0;
};

class Receiver
{
public:
    Receiver(std::map<std::string, std::string> const& options);
    Receiver(std::map<std::string, std::string> const& options, Transport&);
    Receiver(std::map<std::string, std::string> const& options, Transport&, Presentation&);
    ~Receiver();

    void sendDiscover();

    void addDataListener(DataObserver&);
    void removeDataListener(DataObserver&);

    void addControlListener(ControlObserver&);
    void removeControlListener(ControlObserver&);
};

class Sender
{
public:
    Sender(std::map<std::string, std::string> const& options);
    Sender(std::map<std::string, std::string> const& options, Transport&, Presentation&);
    ~Sender();

    void sendPacket(Packet const&);
};

class Transport
{
public:
    enum Type {ALL, DATA, CONTROL};

    virtual ~Transport();

    virtual void sendBytePacket(Type, std::vector<Byte> const&) = 0;
    virtual void addBytePacketObserver(Type, BytePacketObserver&) = 0;
    virtual void removeBytePacketObserver(BytePacketObserver&) = 0;
};

class BytePacketObserver
{
public:
    virtual ~BytePacketObserver() {}
    virtual void onBytePacket(Transport::Type, std::vector<Byte> const&) = 0;
};

}
