%module(directors="1") eitoolkit_csharp

%{
#include <map>
#include <string>
#include "EISender.h"
#include "EIReceiver.h"
using namespace EI;
%}

%include "enums.swg"

%feature("director") EI::DataObserver;
%feature("director") EI::ControlObserver;
%feature("director") EI::BytePacketObserver;

%include "stl.i"

%include "../common/eitoolkit.h"

%template(StringMap) std::map<std::string, std::string>;
%template(ByteVector) std::vector<EI::Byte>;
