find_package(JNI)

if(JNI_FOUND)
  include_directories(${JNI_INCLUDE_DIRS})

  set(CMAKE_SWIG_FLAGS -package de.uni_stuttgart.eitoolkit -Wall)

  set_source_files_properties(eitoolkit.i PROPERTIES CPLUSPLUS ON)
  swig_add_module(eitoolkit_swig_java java eitoolkit.i)
  swig_link_libraries(eitoolkit_swig_java EIToolkit)

  find_package(Java COMPONENTS Development)
  if(Java_Development_FOUND)
    include(UseJava)

    foreach(class ${SWIG_CLASSES})
        list(APPEND JAVA_SOURCE_FILES "${CMAKE_CURRENT_BINARY_DIR}/${class}.java")
    endforeach()

    list(APPEND JAVA_SOURCE_FILES ${CMAKE_CURRENT_BINARY_DIR}/eitoolkit_swig_java.java)
    list(APPEND JAVA_SOURCE_FILES ${CMAKE_CURRENT_BINARY_DIR}/eitoolkit_swig_javaJNI.java)

    set_source_files_properties(${JAVA_SOURCE_FILES} GENERATED)
    source_group(Generated FILES ${JAVA_SOURCE_FILES})
    # TODO problems with parallel make
    add_jar(eitoolkit_swig_java-jni ${JAVA_SOURCE_FILES} DEPENDS eitoolkit_swig_java)

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libeitoolkit-jni.so DESTINATION jar)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/eitoolkit_swig_java-jni.jar DESTINATION jar)
  endif()
endif(JNI_FOUND)
