%{
#include <map>
#include <string>
#include "EIToolkit.h"

using namespace EI;
%}

%include <enums.swg>
%include <std_shared_ptr.i>
%include <stl.i>

/*
%shared_ptr(EI::Packet)
%shared_ptr(EI::DataPacket)
%shared_ptr(EI::DescriptionPacket)
%shared_ptr(EI::DiscoverPacket)
*/

%feature("director") EI::DataObserver;
%feature("director") EI::ControlObserver;
%feature("director") EI::BytePacketObserver;

%include "eitoolkit.h"

%template(StringMap) std::map<std::string, std::string>;
%template(ValueMap) std::map<std::string, EI::Value>;
%template(ByteVector) std::vector<EI::Byte>;
%template(DescriptionPair) std::pair<EI::Value::Type, std::string>;
%template(DescriptionMap) std::map<std::string, std::pair<EI::Value::Type, std::string> >;
