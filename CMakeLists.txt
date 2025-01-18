cmake_minimum_required(VERSION 3.10)

project(MyQtProject VERSION 1.0 LANGUAGES CXX)

find_package(Qt6 COMPONENTS Widgets OpenGL OpenGLWidgets REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MyQtProject
    main.cc        
    mainwindow.cc  
    parser.cc 
    modelviewer.cc
)

add_definitions(-DGL_SILENCE_DEPRECATION=1)

target_link_libraries(MyQtProject PRIVATE Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets)

set_target_properties(MyQtProject PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)
