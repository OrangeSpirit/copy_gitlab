# Минимальная версия CMake и проект
cmake_minimum_required(VERSION 3.10)

project(MyQtProject VERSION 1.0 LANGUAGES CXX)

# Найти необходимые компоненты Qt
find_package(Qt6 COMPONENTS Widgets OpenGL OpenGLWidgets Core Gui REQUIRED)

# Установить стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавить поддиректорию со сборкой статической библиотеки
add_subdirectory(gif)

# Добавляем исполняемый файл
add_executable(MyQtProject
    main.cc
    mainwindow.cc
    parser.cc
    modelviewer.cc
)

# Связать Qt библиотеки
target_link_libraries(MyQtProject PRIVATE
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    Qt6::Core
    Qt6::Gui
    ${CMAKE_CURRENT_SOURCE_DIR}/gif/libgif.a
)

# Указать свойства для автоматической обработки Qt
set_target_properties(MyQtProject PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)
