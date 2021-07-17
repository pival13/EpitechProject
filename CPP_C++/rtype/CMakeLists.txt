cmake_minimum_required(VERSION 3.0.0)
project(R-Type)

set(CONAN_CMAKE_SILENT_OUTPUT True)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS)

if(WIN32)
add_compile_options(/W4 /D_WIN32_WINNT=0x0601)
else()
add_compile_options(-Wall -Wextra -O2)
endif()

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_BUILD_TYPE Debug)#TODO Remove at Release

add_subdirectory(RTypeObjects)
add_subdirectory(factory)
add_subdirectory(client)
add_subdirectory(server)