%module(directors="1") eitoolkit_java

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

%include "stl.i"

%include "../common/eitoolkit.h"

%template(StringMap) std::map<std::string, std::string>;
%template(ByteVector) std::vector<EI::Byte>;

%pragma(java) jniclasscode=%{
  static {
    try {
        System.loadLibrary("eitoolkit-jni");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library failed to load. \n" + e);
      System.exit(1);
    }
  }
%}
