cmake_minimum_required(VERSION 3.0.0)

set(BINARY_NAME r-type_server)
project(${BINARY_NAME})

#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup(NO_OUTPUT_DIRS)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_BUILD_TYPE Debug)#TODO Remove at Release

file(GLOB SOURCES
    "communication/*.cpp"
    "communication/action/*.cpp"
    "communication/udp/*.cpp"
    "*.cpp"
    "game/*.cpp"
    "../factory/*.cpp"
    "../lib/*.cpp"
)

include_directories(
    "${PROJECT_SOURCE_DIR}"
    "${CMAKE_INCLUDE_PATH}"
    ../RTypeObjects
    ../gameObjects
    ../structures
    ../factory
    ../lib
)

add_executable(${BINARY_NAME}
    ${SOURCES}
)
set_target_properties(${BINARY_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"#"${PROJECT_SOURCE_DIR}/.."
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}"#"${PROJECT_SOURCE_DIR}/.."
    DEBUG_POSTFIX "_d"
)

if(UNIX)
    target_link_libraries(${BINARY_NAME} PUBLIC dl)
endif()

target_link_libraries(${BINARY_NAME} PUBLIC "${CONAN_LIBS}" "RTGameEngine")
