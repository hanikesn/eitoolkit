include(EnableCXX11)
include(EnableWarnings)

enable_CXX11()
enable_Warnings()

add_executable(combined combined.cpp)
add_executable(simple_server simple_server.cpp)
add_executable(simple_receiver simple_receiver.cpp)
add_executable(push push.cpp)
add_executable(count count.cpp)
target_link_libraries(combined EIToolkit)
target_link_libraries(simple_server EIToolkit)
target_link_libraries(simple_receiver EIToolkit)
target_link_libraries(push EIToolkit)
target_link_libraries(count EIToolkit)

include_directories("${CMAKE_SOURCE_DIR}/library/include" "${CMAKE_BINARY_DIR}/library/")
