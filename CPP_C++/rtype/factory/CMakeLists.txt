cmake_minimum_required(VERSION 3.0.0)

project(r-type_factory)

#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup(NO_OUTPUT_DIRS)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB CLASSES
    "enemy/*.hpp"
    "missile/*.hpp"
    "player/*.hpp"
    "obstacle/*.hpp"
    "powerup/*.hpp"
)

include_directories(
    "${PROJECT_SOURCE_DIR}"
    "${CMAKE_INCLUDE_PATH}"
    ../RTypeObjects
    ../gameObjects
    ../structures
    ../server
    ../lib
)

foreach(s ${CLASSES})
    string(REGEX REPLACE "^.*[/\\]([^/\\]+)[/\\][^/\\]+\\.hpp$" "\\1" dir ${s})
    string(REGEX REPLACE "^.*[/\\]([^/\\]+)\\.hpp$" "\\1" file ${s})

    add_library(${file} SHARED "${dir}/${file}.cpp")
    set_target_properties(${file} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/${dir}"
            RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/${dir}"
            LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/${dir}"
    )
    target_link_libraries(${file} PUBLIC "${CONAN_LIBS}" "RTGameEngine")
endforeach()
