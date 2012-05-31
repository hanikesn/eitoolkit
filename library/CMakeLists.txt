include(GenerateExportHeader)
include(CheckIncludeFileCXX)
include(CheckCXXCompilerFlag)
include(EnableCXX11)
include(EnableWarnings)

check_CXX11()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11_FLAG}")
enable_Warnings()

set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} ${CXX11_FLAG}")
check_include_file_CXX(thread HAVE_THREAD_H)

if(MSVC)
  set(Boost_USE_STATIC_LIBS ON)
endif()

set(BOOST_components system)

if(NOT HAVE_THREAD_H)
  list(APPEND BOOST_components thread)
endif()

find_package(Boost COMPONENTS ${BOOST_components} REQUIRED)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIR})
  link_directories(${Boost_LIBRARY_DIRS})
  add_definitions(-DBOOST_ALL_NO_LIB)
  # for boost::asio
  if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0501)
  endif()
endif(Boost_FOUND)

set(HEADER_FILES
  include/EIJSONPresentation.h
  include/EIBlockingReceiver.h
  include/EIDataMessage.h
  include/EIDiscoverPacket.h
  include/EIDescription.h
  include/EIDescriptionPacket.h
  include/EIPacket.h
  include/EIPrerequisites.h
  include/EIPresentation.h
  include/EIReceiver.h
  include/EISender.h
  include/EIToolkit.h
  include/EITransport.h
  include/EIUDPTransport.h
  include/EIValue.h
  ${CMAKE_CURRENT_BINARY_DIR}/eitoolkit_export.h
  ${CMAKE_CURRENT_BINARY_DIR}/EIToolkitConfig.h
)

set(SOURCE_FILES
  src/EIBlockingReceiver.cpp
  src/EIJSONPresentation.cpp
  src/EIDataMessage.cpp
  src/EIDiscoverPacket.cpp
  src/EIDescription.cpp
  src/EIDescriptionPacket.cpp
  src/EIPacket.cpp
  src/EISender.cpp
  src/EIReceiver.cpp
  src/EIUDPTransport.cpp
  src/EIValue.cpp
  src/EIThread.h
)

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/EIToolkitConfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/EIToolkitConfig.h"
  )

set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/EIToolkitConfig.h GENERATED)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/../json_spirit)

add_compiler_export_flags()

add_library(EIToolkit SHARED ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(EIToolkit ${Boost_LIBRARIES} json_spirit)

generate_export_header(EIToolkit)

install(TARGETS EIToolkit DESTINATION lib)
install(FILES ${HEADER_FILES} DESTINATION include)

add_subdirectory(swig)
