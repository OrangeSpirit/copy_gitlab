cmake_minimum_required(VERSION 3.10)

project(test_viewer VERSION 1.0 LANGUAGES CXX)

find_package(Qt6 COMPONENTS Widgets OpenGL OpenGLWidgets REQUIRED Core Gui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

#add_compile_options(-Wall -Wextra -Werror)

#add_compile_options(-lgtest -lgcov --coverage -lstdc++)

set(SOURCES
    ../modelviewer.cc
    test.cc
)

add_executable(test_viewer ${SOURCES})

add_definitions(-DGL_SILENCE_DEPRECATION=1)

target_link_libraries(test_viewer PRIVATE
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    Qt6::Core
    Qt6::Gui
    gtest
    gtest_main
    ${CMAKE_CURRENT_SOURCE_DIR}/../gif/libgif.a
)

add_definitions(-DGL_SILENCE_DEPRECATION=1)

target_link_libraries(test_viewer PRIVATE
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    Qt6::Core
    Qt6::Gui
    ${CMAKE_CURRENT_SOURCE_DIR}/../gif/libgif.a
)

set_target_properties(test_viewer PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)
