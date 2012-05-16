find_package(JNI)
include_directories(${JNI_INCLUDE_DIRS})

set(CMAKE_SWIG_FLAGS -package de.uni_stuttgart -Wall)

set_source_files_properties(eitoolkit.i PROPERTIES CPLUSPLUS ON)
swig_add_module(eitoolkit-jni java eitoolkit.i)
swig_link_libraries(eitoolkit-jni eitoolkit)
