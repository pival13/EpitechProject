#Basics informations
cmake_minimum_required(VERSION 3.0.0)
project(Babel)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS ./*.hpp)

include_directories("${PROJECT_SOURCE_DIR}" "${CMAKE_INCLUDE_PATH}")

add_executable(babel_server
    ../GetOpt.cpp
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(babel_server PRIVATE "${CONAN_LIBS}")
