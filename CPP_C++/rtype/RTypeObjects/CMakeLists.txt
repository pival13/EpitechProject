cmake_minimum_required(VERSION 3.0.0)

project(r-type_gameEngine)

#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup(NO_OUTPUT_DIRS)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES
    "*.cpp"
    "../gameObjects/*.cpp"
)

include_directories(
    "${PROJECT_SOURCE_DIR}"
    "${CMAKE_INCLUDE_PATH}"
    ../gameObjects
    ../structures
    ../factory
    ../server
    ../lib
)

if(WIN32)
    add_library(RTGameEngine STATIC
        ${SOURCES} ../server/game/RTypeExtern.cpp
    )
else()
    add_library(RTGameEngine SHARED
        ${SOURCES} ../server/game/RTypeExtern.cpp
    )
endif()
#set_target_properties(RTGameEngine PROPERTIES
#    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"#"${PROJECT_SOURCE_DIR}/.."
#    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}"
#    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}"#"${PROJECT_SOURCE_DIR}/.."
#)
target_link_libraries(RTGameEngine PUBLIC "${CONAN_LIBS}")
