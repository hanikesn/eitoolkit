find_package(SWIG)
if(SWIG_FOUND)
  include(${SWIG_USE_FILE})

  add_subdirectory(java)
endif(SWIG_FOUND)
