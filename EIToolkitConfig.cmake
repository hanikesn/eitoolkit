get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(${SELF_DIR}/EIToolkit-targets.cmake)
get_filename_component(EIToolkit_INCLUDE_DIR "${SELF_DIR}/../../include/" ABSOLUTE)
