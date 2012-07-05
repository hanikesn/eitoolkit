cmake_minimum_required(VERSION 2.8.6)
project(EIToolkit)

include(CMakeDependentOption)

set(EIToolkit_VERSION_MAJOR 0)
set(EIToolkit_VERSION_MINOR 1)
set(EIToolkit_VERSION_PATCH 1)

set(EIToolkit_VERSION_STRING "${EIToolkit_MAJOR_VERSION}.${EIToolkit_MINOR_VERSION}.${EIToolkit_PATCH_VERSION}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif()

option(ENABLE_BINDINGS "Build bindings")
cmake_dependent_option(ENABLE_JAVA "Build the Java bindings" OFF "ENABLE_BINDINGS" OFF)
cmake_dependent_option(ENABLE_CSHARP "Build the CSharp bindings" OFF "ENABLE_BINDINGS" OFF)

add_subdirectory(library)

option(ENABLE_DOCUMENTATION "Build documentation")
if(ENABLE_DOCUMENTATION)
  add_subdirectory(doc)
endif()
option(ENABLE_EXAMPLES "Build examples")
if(ENABLE_EXAMPLES)
  add_subdirectory(examples)
endif()

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
