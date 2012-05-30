find_package(JNI)

if(JNI_FOUND)
  include_directories(${JNI_INCLUDE_DIRS})

  set(CMAKE_SWIG_FLAGS -package de.uni_stuttgart.eitoolkit -Wall)

  if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
    # the swig generated code ist not aliasing safe
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing")
  endif()
  set_source_files_properties(eitoolkit.i PROPERTIES CPLUSPLUS ON)
  set(SWIG_MODULE_eitoolkit_java_EXTRA_DEPS ${SWIG_MODULE_EXTRA_DEPS})
  swig_add_module(eitoolkit_java java eitoolkit.i)
  swig_link_libraries(eitoolkit_java EIToolkit)

  install(TARGETS eitoolkit_java DESTINATION java)

  foreach(class ${SWIG_CLASSES})
    list(APPEND JAVA_SOURCE_FILES "${CMAKE_CURRENT_BINARY_DIR}/${class}.java")
  endforeach()

  list(APPEND JAVA_SOURCE_FILES ${CMAKE_CURRENT_BINARY_DIR}/eitoolkit_java.java)
  list(APPEND JAVA_SOURCE_FILES ${CMAKE_CURRENT_BINARY_DIR}/eitoolkit_javaJNI.java)

  set_source_files_properties(${JAVA_SOURCE_FILES} GENERATED)
  source_group(Generated FILES ${JAVA_SOURCE_FILES})
  set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${JAVA_SOURCE_FILES}")

  find_package(Java COMPONENTS Development)
  if(Java_Development_FOUND)
    include(UseJava)

    add_jar(eitoolkit_java_jni ${JAVA_SOURCE_FILES})
    add_dependencies(eitoolkit_java_jni eitoolkit_java)

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/eitoolkit_java_jni.jar DESTINATION java)
  endif()
endif(JNI_FOUND)
