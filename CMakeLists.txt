cmake_minimum_required(VERSION 3.10)

project(3DViewer_v2.0 VERSION 1.0 LANGUAGES CXX)

find_package(Qt6 COMPONENTS Widgets OpenGL OpenGLWidgets REQUIRED Core Gui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

#add_compile_options(-Wall -Wextra -Werror)

add_subdirectory(gif)

add_executable(3DViewer_v2.0
    main.cc        
    mainwindow.cc  
    model.cc 
    modelviewer.cc
    controller.cc
)

add_definitions(-DGL_SILENCE_DEPRECATION=1)

target_link_libraries(3DViewer_v2.0 PRIVATE
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    Qt6::Core
    Qt6::Gui
    ${CMAKE_CURRENT_SOURCE_DIR}/gif/libgif.a
)

set_target_properties(3DViewer_v2.0 PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)
