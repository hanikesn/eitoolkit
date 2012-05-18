include (GenerateExportHeader)

find_package(Boost COMPONENTS system thread)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
	link_directories(${Boost_LIBRARY_DIRS})
	add_definitions(-DBOOST_ALL_NO_LIB)
	# for boost::asio
	add_definitions(-D_WIN32_WINNT=0x0501)
endif(Boost_FOUND)

set (HEADER_FILES
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

set (SOURCE_FILES
  src/EISender.cpp
  src/EIReceiver.cpp
  src/EIUDPTransport.cpp
)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_compiler_export_flags()

add_library(EIToolkit SHARED ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(EIToolkit ${Boost_LIBRARIES})

generate_export_header(EIToolkit)

install(TARGETS EIToolkit DESTINATION lib)
install(FILES ${HEADER_FILES} DESTINATION include)

add_subdirectory(swig)
