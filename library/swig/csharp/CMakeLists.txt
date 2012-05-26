  set(CMAKE_SWIG_FLAGS -namespace de.uni_stuttgart.eitoolkit -Wall)

  set_source_files_properties(eitoolkit.i PROPERTIES CPLUSPLUS ON)
  swig_add_module(eitoolkit_swig_csharp csharp eitoolkit.i)
  swig_link_libraries(eitoolkit_swig_csharp EIToolkit)
