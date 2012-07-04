cmake_minimum_required(VERSION 2.6)
project(Example)

find_package(EIToolkit REQUIRED)

include_directories(${EIToolkit_INCLUDE_DIR})

add_executable(example example.cpp)
target_link_libraries(example EIToolkit)
