%module(directors="1") eitoolkit_csharp

%include <enums.swg>

%typemap(csattributes) EI::DataSeriesInfo::Property "[Flags]"

%include "../common/eitoolkit.i"
