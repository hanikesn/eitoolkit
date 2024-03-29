set(CMAKE_SWIG_FLAGS -namespace de.uni_stuttgart.eitoolkit -Wall)

set_source_files_properties("eitoolkit.i" PROPERTIES CPLUSPLUS ON)
set(SWIG_MODULE_eitoolkit_csharp_EXTRA_DEPS ${SWIG_MODULE_EXTRA_DEPS})
swig_add_module(eitoolkit_csharp csharp eitoolkit.i)
swig_link_libraries(eitoolkit_csharp EIToolkit)

install(TARGETS eitoolkit_csharp DESTINATION csharp)

if(ENABLE_CSHARP)
  enable_language(CSharp)
  foreach(class ${SWIG_CLASSES})
    list(APPEND CSHARP_SOURCE_FILES "${CMAKE_CURRENT_BINARY_DIR}/${class}.cs")
  endforeach()

  list(APPEND CSHARP_SOURCE_FILES ${CMAKE_CURRENT_BINARY_DIR}/eitoolkit_csharp.cs)
  list(APPEND CSHARP_SOURCE_FILES ${CMAKE_CURRENT_BINARY_DIR}/eitoolkit_csharpPINVOKE.cs)

  set_source_files_properties(${CSHARP_SOURCE_FILES} GENERATED)
  source_group(Generated FILES ${CSHARP_SOURCE_FILES})
  set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${CSHARP_SOURCE_FILES}")

  mark_as_advanced(GAC_DIR)

  csharp_add_library(eitoolkit_csharp_net ${CSHARP_SOURCE_FILES} DEPENDS eitoolkit_csharp)
  add_dependencies(eitoolkit_csharp_net eitoolkit_csharp)

  install_assembly(eitoolkit_csharp_net NO_GAC DESTINATION csharp)
endif()
