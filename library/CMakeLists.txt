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

set(Boost_DEBUG FALSE CACHE BOOL "Set this to debug the finding of boost")

find_package(Boost COMPONENTS ${BOOST_components} REQUIRED)
mark_as_advanced (Boost_LIB_DIAGNOSTIC_DEFINITIONS Boost_DIR)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
add_definitions(-DBOOST_ALL_NO_LIB -DBOOST_ASIO_SEPARATE_COMPILATION)
# for boost::asio
if(WIN32)
  add_definitions(-D_WIN32_WINNT=0x0501)
endif()

set(HEADER_FILES
  include/EIBlockingReceiver.h
  include/EIDataMessage.h
  include/EIDescription.h
  include/EIDescriptionMessage.h
  include/EIDiscoveryMessage.h
  include/EIException.h
  include/EIJSONPresentation.h
  include/EIMessage.h
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
  src/EIDataMessage.cpp
  src/EIDescription.cpp
  src/EIDescriptionMessage.cpp
  src/EIDiscoveryMessage.cpp
  src/EIException.cpp
  src/EIJSONPresentation.cpp
  src/EIMessage.cpp
  src/EIPresentation.cpp
  src/EIReceiver.cpp
  src/EISender.cpp
  src/EIThread.h
  src/EITransport.cpp
  src/EIUDPTransport.cpp
  src/EIValue.cpp
  src/PresentationManager.h
  src/PresentationManager.cpp
  src/boost_asio_impl.cpp
  src/helpers.h
)

option(ENABLE_PROTOBUF "Build with the protobuf presentation.")
if(ENABLE_PROTOBUF)
  find_package(Protobuf REQUIRED)
  if(PROTOBUF_FOUND)
    include_directories(${PROTOBUF_INCLUDE_DIRS})
    protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS protobuf/EIMessage.proto)
    list(APPEND SOURCE_FILES src/EIProtobufPresentation.cpp ${PROTO_SRCS})
    list(APPEND HEADER_FILES include/EIProtobufPresentation.h ${PROTO_HDRS})
    set(HAVE_PROTOBUF 1)
  endif()
endif()

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/EIToolkitConfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/EIToolkitConfig.h"
  )

set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/EIToolkitConfig.h GENERATED)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/../rapidjson)

add_compiler_export_flags()

add_library(EIToolkit SHARED ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(EIToolkit ${Boost_LIBRARIES})
if(OPTION_PROTOBUF)
  target_link_libraries(EIToolkit ${PROTOBUF_LIBRARIES})
endif()

if(HAVE_THREAD_H AND CMAKE_COMPILER_IS_GNUCXX)
  # Check gcc version
  execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
  if(GCC_VERSION VERSION_LESS 4.7)
    find_package(Threads REQUIRED)
    target_link_libraries(EIToolkit ${CMAKE_THREAD_LIBS_INIT})
  endif()
endif()

generate_export_header(EIToolkit)

install(TARGETS EIToolkit EXPORT EIToolkit-targets DESTINATION lib)
install(FILES ${HEADER_FILES} DESTINATION include)

if(ENABLE_BINDINGS)
  add_subdirectory(swig)
endif()
