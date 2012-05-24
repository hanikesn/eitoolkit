include(EnableCXX11)
include(EnableWarnings)

enable_CXX11()
enable_Warnings()

if(WIN32)
  # We need to copy the dll so the examples find the library
  add_custom_command(TARGET combined POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        $<TARGET_FILE_DIR:EIToolkit>/EIToolkit.dll
        $<TARGET_FILE_DIR:combined>
		COMMENT "Copying dlls")
endif()

add_executable(combined combined.cpp)
add_executable(simple_server simple_server.cpp)
add_executable(simple_receiver simple_receiver.cpp)
target_link_libraries(combined EIToolkit)
target_link_libraries(simple_server EIToolkit)
target_link_libraries(simple_receiver EIToolkit)

include_directories("${CMAKE_SOURCE_DIR}/library/include" "${CMAKE_BINARY_DIR}/library/")
