cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_COMPILER "/usr/bin/g++" CACHE STRING "g++ compiler" FORCE)
set(CMAKE_C_COMPILER "/usr/bin/gcc" CACHE STRING "gcc compiler" FORCE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -lncurses")

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS ON)

project(simulator_visual CXX)

find_package( OpenAL REQUIRED )
message( "OPENAL_INCLUDE_DIR = ${OPENAL_INCLUDE_DIR}" )
include_directories(${OPENAL_INCLUDE_DIR})
include_directories(/usr/local/include/AL)

find_package(Boost 1.72.0 REQUIRED)


message(${OPENAL_LIBRARY})

include_directories(audio djcon)
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB MAIN_SOURCE audio/*.cpp djcon/*.cpp)
add_executable(a.out ${MAIN_SOURCE} main.cpp)
target_link_libraries(a.out ${OPENAL_LIBRARY} )


file(GLOB TEST_SOURCES test/*.cpp)
foreach(TEST_SRC ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
    add_executable(${TEST_NAME} ${MAIN_SOURCE} ${TEST_SRC})
    target_link_libraries(${TEST_NAME} ${OPENAL_LIBRARY})
    target_link_libraries(${TEST_NAME} ${Boost_LIBRARIES})
endforeach()
