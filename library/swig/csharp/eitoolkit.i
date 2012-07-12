%module(directors="1") eitoolkit_csharp

%typemap(csattributes) EI::DataSeriesInfo::Property "[Flags]"

%include "../common/eitoolkit.i"
