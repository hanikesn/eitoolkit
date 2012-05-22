include(GenerateExportHeader)
include(CheckCXXCompilerFlag)

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
  check_cxx_compiler_flag(-std=c++11 HAS_CXX11)
  if(HAS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
  endif()
endif()
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS system thread REQUIRED)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIR})
  link_directories(${Boost_LIBRARY_DIRS})
  add_definitions(-DBOOST_ALL_NO_LIB)
  # for boost::asio
  add_definitions(-D_WIN32_WINNT=0x0501)
endif(Boost_FOUND)

set(HEADER_FILES
  include/EIJSONPresentation.h
  include/EIDataPacket.h
  include/EIPacket.h
  include/EIPrerequisites.h
  include/EIPresentation.h
  include/EIReceiver.h
  include/EISender.h
  include/EIToolkit.h
  include/EITransport.h
  include/EIUDPTransport.h
  ${CMAKE_CURRENT_BINARY_DIR}/eitoolkit_export.h
)

set(SOURCE_FILES
  src/EIJSONPresentation.cpp
  src/EIDataPacket.cpp
  src/EIPacket.cpp
  src/EISender.cpp
  src/EIReceiver.cpp
  src/EIUDPTransport.cpp
)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_compiler_export_flags()

add_library(EIToolkit SHARED ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(EIToolkit ${Boost_LIBRARIES} json_spirit)

generate_export_header(EIToolkit)

install(TARGETS EIToolkit DESTINATION lib)
install(FILES ${HEADER_FILES} DESTINATION include)

add_subdirectory(swig)
