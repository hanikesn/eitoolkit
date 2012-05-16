%module(directors="1") EIToolkit

%{
#include <map>
#include <string>
#include "EISender.h"
#include "EIReceiver.h"
using namespace EI;
%}

%include "enums.swg"
%javaconst(1);

%feature("director") EI::DataObserver;
%feature("director") EI::ControlObserver;
%feature("director") EI::BytePacketObserver;

%include "std_vector.i"
%include "std_map.i"
%include "std_string.i"

%include "EIPrerequisites.h"
%include "EIPacket.h"
%include "EITransport.h"
%include "EIPresentation.h"
%include "EIPacket.h"
%include "EISender.h"
%include "EIReceiver.h"

%template(StringMap) std::map<std::string, std::string>;
%template(ByteVector) std::vector<EI::Byte>;

%pragma(java) jniclasscode=%{
  static {
    try {
        System.loadLibrary("eitoolkit");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library failed to load. \n" + e);
      System.exit(1);
    }
  }
%}
