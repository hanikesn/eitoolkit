set (HEADER_FILES
  include/EIToolkit.h
)

set (SOURCE_FILES
  src/EISender.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(eitoolkit SHARED ${SOURCE_FILES})
