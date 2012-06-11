find_package(SWIG REQUIRED)
mark_as_advanced ( SWIG_DIR SWIG_VERSION )
include(${SWIG_USE_FILE})

set(SWIG_CLASSES
  BlockingReceiver
  ByteVector
  CommunicationListener
  DataListener
  DataMessage
  DataMessageVector
  DataSeriesInfo
  Description
  DataSeriesInfoMap
  DescriptionMessage
  DiscoveryMessage
  Message
  PacketListener
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
