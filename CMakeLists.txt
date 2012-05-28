cmake_minimum_required (VERSION 2.8.6)
project (EIToolkit)

set(EIToolkit_VERSION_MAJOR 0)
set(EIToolkit_VERSION_MINOR 1)
set(EIToolkit_VERSION_PATCH 1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

include(CPack)

add_subdirectory(json_spirit)
add_subdirectory(library)
add_subdirectory(examples)
