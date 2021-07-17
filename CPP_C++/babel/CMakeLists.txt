#Basics informations
cmake_minimum_required(VERSION 3.0.0)
project(Babel)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(UI)
add_subdirectory(server)