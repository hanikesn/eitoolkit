set (HEADER_FILES
  include/EIPacket.h
  include/EIPrerequisites.h
  include/EIPresentation.h
  include/EIReceiver.h
  include/EISender.h
  include/EIToolkit.h
  include/EITransport.h
)

set (SOURCE_FILES
  src/EISender.cpp
  src/EIReceiver.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(eitoolkit SHARED ${SOURCE_FILES})
