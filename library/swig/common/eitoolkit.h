namespace EI
{
typedef char Byte;

class PacketObserver;
class ControlObserver;
class DataObserver;
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
    Value(std::string const&);
    Value(double);
    Value(Value const&);
    ~Value();

    Type getType() const;

    std::string const& asString();
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

class Description
{
public:
    Description(const std::string& device_type);
    Description(const Description& other);
    ~Description();

    std::string getDeviceType() const;

    void addDataSeries(const std::string& name, const DataSeriesInfo& info);
    std::map<std::string, std::pair<Value::Type, std::string> > values() const;
};

class Message
{
public:
    Message(std::string const& sender, std::string const& msgtype);
    Message(Message const& other);
    virtual ~Message();

    std::string const& getSender() const;
    std::string const& getMsgtype() const;
};

class DescriptionMessage : public Message
{
public:
    DescriptionMessage(std::string const& sender, Description const& description);

    Description const& getDescription();

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
    Value const& get(std::string const& name) const;
    std::map<std::string, Value> getValues() const;

    void setString(std::string const& name, std::string const& value);
    std::string getString(std::string const& name) const;

    void setDouble(std::string const& name, double value);
    double getDouble(std::string const& name) const;
};

class Presentation
{
public:
    virtual ~Presentation();
    void encode(Message const&, std::vector<Byte> &) = 0;
    // Shared Pointer machen probleme
    // virtual std::shared_ptr<Message> decode(std::vector<Byte> const&) = 0;
};

class DataObserver
{
public:
    virtual ~DataObserver() {}
    virtual void onMessage(DataMessage const&) = 0;
};

class ControlObserver
{
public:
    virtual ~ControlObserver() {}
    virtual void onMessage(Message const&) = 0;
};

class Receiver
{
public:
    Receiver(std::map<std::string, std::string> const& options);
    Receiver(std::map<std::string, std::string> const& options, Transport&);
    Receiver(std::map<std::string, std::string> const& options, Transport&, Presentation&);
    ~Receiver();

    void discoverSenders();

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

    void sendMessage(Message const&);
};

class Transport
{
public:
    enum Type {ALL, DATA, CONTROL};

    virtual ~Transport();

    virtual void sendPacket(Type, std::vector<Byte> const&) = 0;
    virtual void addPacketObserver(Type, PacketObserver&) = 0;
    virtual void removePacketObserver(PacketObserver&) = 0;
};

class PacketObserver
{
public:
    virtual ~PacketObserver() {}
    virtual void onPacket(Transport::Type, std::vector<Byte> const&) = 0;
};

class BlockingReceiver
{
public:
    BlockingReceiver(std::map<std::string, std::string> const& options);
    BlockingReceiver(std::map<std::string, std::string> const& options, Transport& transport);
    BlockingReceiver(std::map<std::string, std::string> const& options, Transport& transport, Presentation& presentation);
    ~BlockingReceiver();

    std::vector<DataMessage> getMessages();
    int hasMessages();
    void waitForMessages(int milliseconds);
};

}
