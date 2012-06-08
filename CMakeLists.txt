cmake_minimum_required(VERSION 2.8.6)
project(EIToolkit)

set(EIToolkit_VERSION_MAJOR 0)
set(EIToolkit_VERSION_MINOR 1)
set(EIToolkit_VERSION_PATCH 1)

set(EIToolkit_VERSION_STRING "${EIToolkit_MAJOR_VERSION}.${EIToolkit_MINOR_VERSION}.${EIToolkit_PATCH_VERSION}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

include(CPack)

add_subdirectory(library)
add_subdirectory(doc)
add_subdirectory(examples)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/EIToolkitConfigVersion.cmake.in
               ${CMAKE_CURRENT_BINARY_DIR}/EIToolkitConfigVersion.cmake
               @ONLY)

# for build tree
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/EIToolkitConfig.cmake.in
               ${CMAKE_CURRENT_BINARY_DIR}/EIToolkitConfig.cmake
               @ONLY)

# Create config for build tree
export(PACKAGE EIToolkit)
export(TARGETS EIToolkit APPEND FILE EIToolkitConfig.cmake)

# create config for install tree
install(EXPORT EIToolkit-targets DESTINATION lib/EIToolkit)
install(FILES EIToolkitConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/EIToolkitConfigVersion.cmake DESTINATION lib/EIToolkit)

install(FILES cmake/EnableCXX11.cmake DESTINATION lib/EIToolkit)
