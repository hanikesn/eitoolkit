set(DOXYFILE_LATEX "OFF")
set(DOXYFILE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/library/include/")
include(UseDoxygen)

if(DOXYGEN_FOUND)
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc DESTINATION ".")
endif()

install(DIRECTORY "examples" DESTINATION "doc")
