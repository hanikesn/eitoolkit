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

class Value
{
public:
    enum Type {EMPTY, DOUBLE, STRING};

    Value();
    Value(std::string const&);
    Value(double);
    Value(Value const&);
    ~Value();

    Type getType() const;

    std::string const& asString();
};

class Description
{
public:
    void addDataStream(std::string const& name, std::pair<Value::Type, std::string> const& info);

    std::map<std::string, std::pair<Value::Type, std::string> > values();
};

class Packet
{
public:
    Packet(std::string const& sender, std::string const& msgtype);
    Packet(Packet const& other);
    virtual ~Packet();

    std::string const& getSender() const;
    std::string const& getMsgtype() const;
};

class DescriptionPacket : public Packet
{
public:
    DescriptionPacket(std::string const& sender, Description const& description);

    Description const& getDescription();

    static char const* const IDENTIFIER;
};

class DiscoverPacket : public Packet
{
public:
    DiscoverPacket(std::string const& sender);

    static char const* const IDENTIFIER;
};

class DataPacket : public Packet
{
public:
    DataPacket(std::string const& sender);
    DataPacket(DataPacket const& other);

    void set(std::string const&, Value const&);
    Value const& get(std::string const&) const;
    std::map<std::string, Value> const& getValues() const;

    void setString(std::string const&, std::string const&);
    std::string const& getString(std::string const&) const;

    void setDouble(std::string const&, double);
    double getDouble(std::string const&) const;

    static char const* const IDENTIFIER;
};

class Presentation
{
public:
    virtual ~Presentation();
    void encode(Packet const&, std::vector<Byte> &) = 0;
    // Shared Pointer machen probleme
    // virtual std::shared_ptr<Packet> decode(std::vector<Byte> const&) = 0;
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
    Sender(Description const&, std::map<std::string, std::string> const& options);
    Sender(Description const&, std::map<std::string, std::string> const& options, Transport&, Presentation&);
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
