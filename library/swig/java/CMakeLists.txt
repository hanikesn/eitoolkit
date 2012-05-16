find_package(JNI)
if (JNI_FOUND)
  include_directories(${JNI_INCLUDE_DIRS})

  set(CMAKE_SWIG_FLAGS -package de.uni_stuttgart -Wall)

  set_source_files_properties(eitoolkit.i PROPERTIES CPLUSPLUS ON)
  swig_add_module(eitoolkit-jni java eitoolkit.i)
  swig_link_libraries(eitoolkit-jni eitoolkit)
endif(JNI_FOUND)
