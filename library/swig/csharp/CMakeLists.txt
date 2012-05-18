  set(CMAKE_SWIG_FLAGS -namespace de.uni_stuttgart.eitoolkit -Wall)

  set_source_files_properties(eitoolkit.i PROPERTIES CPLUSPLUS ON)
  swig_add_module(eitoolkit-csharp csharp eitoolkit.i)
  swig_link_libraries(eitoolkit-csharp EIToolkit)
