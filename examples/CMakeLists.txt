add_executable(server server.cpp)
target_link_libraries(server EIToolkit)

include_directories("${CMAKE_SOURCE_DIR}/library/include" "${CMAKE_BINARY_DIR}/library/")
