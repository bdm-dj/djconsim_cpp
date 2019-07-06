cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_COMPILER "/usr/bin/g++" CACHE string "g++ compiler" FORCE)
set(CMAKE_C_COMPILER "/usr/bin/gcc" CACHE string "gcc compiler" FORCE)

set(CMAKE_CXX_STANDARD 17)

project(simulator_visual CXX)

find_package(OpenGL REQUIRED)
message(STATUS ${OPENGL_LIBRARIES})
message(STATUS ${OPENGL_INCLUDE_DIR})

find_package(GLUT REQUIRED)
message(STATUS ${GLUT_LIBRARY})
message(STATUS ${GLUT_INCLUDE_DIR})

find_package( Eigen3 REQUIRED )
message( ${EIGEN3_INCLUDE_DIR} )
include_directories()

find_package( OpenAL REQUIRED )
message( "OPENAL_INCLUDE_DIR = ${OPENAL_INCLUDE_DIR}" )
include_directories(${OPENAL_INCLUDE_DIR})



include_directories(
    ${OPENGL_INCLUDE_DIR}
    ${GLUT_INCLUDE_DIR}
    ${EIGEN3_INCLUDE_DIR}
    )

include_directories(audio)
include_directories(${OPENGL_INCLUDE_DIRS})

file(GLOB MAIN_SOURCE *.cpp audio/*.cpp)
add_executable(a.out ${MAIN_SOURCE})

TARGET_LINK_LIBRARIES(a.out
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARY}
    ${OPENAL_LIBRARY}
    )

