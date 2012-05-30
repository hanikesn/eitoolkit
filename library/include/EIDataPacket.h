#ifndef EIDataPacket_H
#define EIDataPacket_H

#include "EIPrerequisites.h"
#include "EIValue.h"
#include "EIPacket.h"

#include <map>

namespace EI
{

class EITOOLKIT_EXPORT DataPacket : public Packet
{
public:
    DataPacket(std::string const& sender);
    DataPacket(DataPacket const& other);
    ~DataPacket();

    DataPacket& operator=(DataPacket const& other);

    void set(std::string const&, Value const&);
    Value const& get(std::string const&) const;
    std::map<std::string, Value> const& getValues() const;

    void setString(std::string const&, std::string const&);
    std::string const& getString(std::string const&) const;

    void setDouble(std::string const&, double);
    double getDouble(std::string const&) const;

    static char const* const IDENTIFIER;

private:
    DataPacket();
    #ifdef SWIGJAVA
    friend jlong Java_de_uni_1stuttgart_eitoolkit_eitoolkit_1javaJNI_new_1DataPacketVector_1_1SWIG_11(JNIEnv *jenv, jclass jcls, jlong jarg1);
    #endif

    class DataPacketImpl;
    DataPacketImpl* pimpl;
};

}

#endif
