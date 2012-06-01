namespace EI
{
typedef char Byte;
typedef std::map<std::string, std::string> StringMap;
typedef std::vector<Byte> ByteVector;

class PacketListener;
class ControlListener;
class DataListener;
class Message;
class Receiver;
class Sender;
class Transport;
class UDPTransport;

class Value
{
public:
    enum Type {EMPTY, DOUBLE, STRING};

    Value();
    Value(std::string const& value);
    Value(double value );

    Value(Value const& other);
    ~Value();

    Type getType() const;

    std::string const& asString() const;
    double asDouble() const;
};

class DataSeriesInfo
{
public:
    enum Property {INTERPOLATABLE=1, STATEFUL=2, HIDDEN=4, HAS_MIN=8, HAS_MAX=16, HAS_MINMAX=24};
    DataSeriesInfo(Value::Type type, Property properties, const std::string& misc);
    DataSeriesInfo(Value::Type type, Property properties, const std::string& misc, double min, double max);

    std::string getMisc() const;

    Value::Type getType() const;

    Property getProperties() const;

    bool hasProperty(Property property) const;

    double getMin() const;
    double getMax() const;
};

typedef std::map<std::string, DataSeriesInfo> DataSeriesInfoMap;

class Description
{
public:
    Description(const std::string& device_type);
    Description(const Description& other);
    ~Description();

    std::string getDeviceType() const;

    void addDataSeries(const std::string& name, const DataSeriesInfo& info);
    DataSeriesInfoMap getDataSeries() const;
};

class Message
{
public:
    Message(std::string const& sender, std::string const& msgtype);
    Message(Message const& other);
    virtual ~Message();

    std::string const& getSender() const;
    std::string const& getMsgType() const;
};

class DescriptionMessage : public Message
{
public:
    DescriptionMessage(std::string const& sender, Description const& description);

    Description getDescription();

    static char const* const IDENTIFIER;
};

class DiscoveryMessage : public Message
{
public:
    DiscoveryMessage(std::string const& sender);

    static char const* const IDENTIFIER;
};

class DataMessage : public Message
{
public:
    static char const* const IDENTIFIER;

    DataMessage(std::string const& sender);
    DataMessage(DataMessage const& other);
    ~DataMessage();

    void set(std::string const& name, Value const& value);
    Value get(std::string const& name) const;
    std::map<std::string, Value> getContent() const;

    void setString(std::string const& name, std::string const& value);
    std::string getString(std::string const& name) const;

    void setDouble(std::string const& name, double value);
    double getDouble(std::string const& name) const;
};

class Presentation
{
public:
    virtual ~Presentation();
    void encode(Message const&, ByteVector &) = 0;
    // Shared Pointer machen probleme
    // virtual std::shared_ptr<Message> decode(ByteVector const&) = 0;
};

class DataListener
{
public:
    virtual ~DataListener();
    virtual void onMessage(DataMessage const&) = 0;
};

class CommunicationListener
{
public:
    virtual ~CommunicationListener();
    virtual void onMessage(Message const&) = 0;
};

class Receiver
{
public:
    Receiver(StringMap const& options);
    Receiver(StringMap const& options, Transport&);
    Receiver(StringMap const& options, Transport&, Presentation&);
    ~Receiver();

    void discoverSenders();

    void addDataListener(DataListener&);
    void removeDataListener(DataListener&);

    void addCommunicationListener(CommunicationListener&);
    void removeCommunicationListener(CommunicationListener&);
};

class Sender
{
public:
    Sender(Description const& description, StringMap const& options);
    Sender(Description const& description, StringMap const& options, Transport&, Presentation&);
    ~Sender();

    void sendMessage(Message const&);
};

class Transport
{
public:
    enum Channel {ALL, DATA, CONTROL};

    virtual ~Transport();

    virtual void sendPacket(Channel, ByteVector const&) = 0;
    virtual void addPacketListener(Channel, PacketListener&) = 0;
    virtual void removePacketListener(PacketListener&) = 0;
};

class PacketListener
{
public:
    virtual ~PacketListener();
    virtual void onPacket(Transport::Channel, ByteVector const&) = 0;
};

class BlockingReceiver
{
public:
    BlockingReceiver(StringMap const& options);
    BlockingReceiver(StringMap const& options, Transport& transport);
    BlockingReceiver(StringMap const& options, Transport& transport, Presentation& presentation);
    ~BlockingReceiver();

    std::vector<DataMessage> getMessages();
    int hasMessages();
    void waitForMessages(int milliseconds);
};

}
