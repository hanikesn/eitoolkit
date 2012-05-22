cmake_minimum_required (VERSION 2.8)
project (EIToolkit)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

add_subdirectory(json_spirit)
add_subdirectory(library)
add_subdirectory(examples)
