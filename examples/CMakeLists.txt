include(EnableCXX11)
include(EnableWarnings)

enable_Warnings()
check_CXX11()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11_FLAG}")

if(MSVC)
  set(Boost_USE_STATIC_LIBS ON)
endif()
find_package(Boost COMPONENTS system chrono thread REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
add_definitions(-DBOOST_ALL_NO_LIB)

add_executable(combined combined.cpp)
add_executable(simple_server simple_server.cpp)
add_executable(simple_receiver simple_receiver.cpp)
add_executable(push push.cpp)
add_executable(count count.cpp)
add_executable(generic_receiver generic_receiver.cpp)
add_executable(sinus_sender sinus_sender.cpp)
add_executable(discrete_sender discrete_sender.cpp)
add_executable(slow_discrete_sender slow_discrete_sender.cpp)
add_executable(sinus_sender_fast sinus_sender_fast.cpp)
target_link_libraries(combined EIToolkit)
target_link_libraries(simple_server EIToolkit)
target_link_libraries(simple_receiver EIToolkit)
target_link_libraries(push EIToolkit ${Boost_LIBRARIES})
target_link_libraries(count EIToolkit)
target_link_libraries(generic_receiver EIToolkit)
target_link_libraries(sinus_sender EIToolkit ${Boost_LIBRARIES})
target_link_libraries(discrete_sender EIToolkit ${Boost_LIBRARIES})
target_link_libraries(slow_discrete_sender EIToolkit ${Boost_LIBRARIES})
target_link_libraries(sinus_sender_fast EIToolkit ${Boost_LIBRARIES})

if(WIN32)
add_custom_target(CopyDLL ALL DEPENDS EIToolkit
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE_DIR:EIToolkit>/EIToolkit.dll
        $<TARGET_FILE_DIR:combined>
		COMMENT "Copying dlls")
endif()

include_directories("${CMAKE_SOURCE_DIR}/library/include" "${CMAKE_BINARY_DIR}/library/")
