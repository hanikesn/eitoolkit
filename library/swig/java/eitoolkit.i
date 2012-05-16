%module EIToolkit

%{
#include <map>
#include <string>
#include "EISender.h"
#include "EIReceiver.h"
using namespace EI;
%}

%include "EISender.h"
%include "EIReceiver.h"
%include "EITransport.h"
%include "EIPresentation.h"


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
