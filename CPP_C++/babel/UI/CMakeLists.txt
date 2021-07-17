cmake_minimum_required(VERSION 3.5)

project(Babel LANGUAGES CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

file(GLOB SOURCES
        ./*.cpp
        ./data_user/*.cpp
        ../audio/*.cpp
        ../Client/*.cpp
    )
file(GLOB HEADERS
        ./*.h
        ./*.hpp
        ./data_user/*.h
        ../audio/*.hpp
        ../Client/*.hpp
    )
file(GLOB UI ./*.ui)

include_directories("${PROJECT_SOURCE_DIR}" "${CMAKE_INCLUDE_PATH}" ../audio)

add_executable(babel_client
    ../GetOpt.cpp
    main.cpp
    ${SOURCES}
    ${HEADERS}
    ${UI}
    qrc.qrc
)

target_link_libraries(babel_client PRIVATE
                            "${CONAN_LIBS}"
                            Qt5::Widgets
                            Qt5::Network
                            )
