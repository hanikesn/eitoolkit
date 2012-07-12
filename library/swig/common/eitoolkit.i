%{

#define EI_FOR_SWIG

#include <map>
#include <string>
#include "EIToolkit.h"

using namespace EI;
%}


%include <std_shared_ptr.i>
%include <stl.i>

/*
%shared_ptr(EI::Packet)
%shared_ptr(EI::DataMessage)
%shared_ptr(EI::DescriptionPacket)
%shared_ptr(EI::DiscoverPacket)
*/

%feature("director") EI::DataListener;
%feature("director") EI::CommunicationListener;
%feature("director") EI::PacketListener;

// DataPacket doesn't have a default constructor, but this constructor would require one, so don't generate it
%ignore std::vector<EI::DataMessage>::vector(size_type);

%include "eitoolkit.h"

%template(StringMap) std::map<std::string, std::string>;
%template(ValueMap) std::map<std::string, EI::Value>;
%template(ByteVector) std::vector<EI::Byte>;
%template(DataMessageVector) std::vector<EI::DataMessage>;
%template(DataSeriesInfoMap) std::map<std::string, EI::DataSeriesInfo>;
