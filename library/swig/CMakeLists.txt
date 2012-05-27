find_package(SWIG)
mark_as_advanced ( SWIG_DIR SWIG_VERSION )
if(SWIG_FOUND)
  include(${SWIG_USE_FILE})

  set(SWIG_CLASSES
    BytePacketObserver
    ByteVector
    ControlObserver
    DataObserver
    DataPacket
    Packet
    Presentation
    Receiver
    Sender
    StringMap
    Transport
  )

  add_subdirectory(java)
  add_subdirectory(csharp)
endif(SWIG_FOUND)
