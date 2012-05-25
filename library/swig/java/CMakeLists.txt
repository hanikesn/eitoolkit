find_package(JNI)

if(JNI_FOUND)
  include_directories(${JNI_INCLUDE_DIRS})

  set(CMAKE_SWIG_FLAGS -package de.uni_stuttgart.eitoolkit -Wall)

  set_source_files_properties(eitoolkit.i PROPERTIES CPLUSPLUS ON)
  swig_add_module(eitoolkit-jni java eitoolkit.i)
  swig_link_libraries(eitoolkit-jni EIToolkit)

  find_package(Java REQUIRED)
  #if(Java_FOUND)
    include(UseJava)
    set(JAVA_SOURCE_FILES
${CMAKE_CURRENT_BINARY_DIR}/BytePacketObserver.java
${CMAKE_CURRENT_BINARY_DIR}/ByteVector.java
${CMAKE_CURRENT_BINARY_DIR}/ControlObserver.java
${CMAKE_CURRENT_BINARY_DIR}/DataObserver.java
${CMAKE_CURRENT_BINARY_DIR}/DataPacket.java
${CMAKE_CURRENT_BINARY_DIR}/EIToolkit.java
${CMAKE_CURRENT_BINARY_DIR}/EIToolkitJNI.java
${CMAKE_CURRENT_BINARY_DIR}/Packet.java
${CMAKE_CURRENT_BINARY_DIR}/Presentation.java
${CMAKE_CURRENT_BINARY_DIR}/Receiver.java
${CMAKE_CURRENT_BINARY_DIR}/Sender.java
${CMAKE_CURRENT_BINARY_DIR}/StringMap.java
${CMAKE_CURRENT_BINARY_DIR}/Transport.java
)
    set_source_files_properties(${JAVA_SOURCE_FILES} GENERATED)
    add_jar(eitoolkit-jni-jar ${JAVA_SOURCE_FILES})

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libeitoolkit-jni.so DESTINATION jar)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/eitoolkit-jni-jar.jar DESTINATION jar)
  #endif()
endif(JNI_FOUND)
