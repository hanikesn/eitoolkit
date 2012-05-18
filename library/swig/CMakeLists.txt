find_package(SWIG)
mark_as_advanced ( SWIG_DIR SWIG_EXECUTABLE SWIG_VERSION )
if(SWIG_FOUND)
  include(${SWIG_USE_FILE})

  add_subdirectory(java)
  add_subdirectory(csharp)
endif(SWIG_FOUND)
