find_package(SWIG)
mark_as_advanced ( SWIG_DIR SWIG_VERSION )
if(SWIG_FOUND)
  include(${SWIG_USE_FILE})

  set(SWIG_CLASSES
    BlockingReceiver
    PacketObserver
    ByteVector
    ControlObserver
    DataObserver
    DataMessage
    DataMessageVector
    DiscoverMessage
    DataSeriesInfo
    Description
    DescriptionMessage
    DescriptionPair
    DescriptionMap
    Message
    Presentation
    Receiver
    Sender
    StringMap
    Transport
    Value
    ValueMap
  )

  set(SWIG_MODULE_EXTRA_DEPS "../common/eitoolkit.h" "../common/eitoolkit.i")

  disable_WarningUnused()

  add_subdirectory(java)
  add_subdirectory(csharp)
endif(SWIG_FOUND)
