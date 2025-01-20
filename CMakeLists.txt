# Минимальная версия CMake и проект
cmake_minimum_required(VERSION 3.10)

project(MyQtProject VERSION 1.0 LANGUAGES CXX)

# Найти необходимые компоненты Qt
find_package(Qt6 COMPONENTS Widgets OpenGL OpenGLWidgets Core Gui REQUIRED)

# Добавляем общий CMake файл для объединенной библиотеки
add_subdirectory(gif)  # Добавление gif/ CMakeLists.txt, который собирает общую библиотеку

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем исполняемый файл
add_executable(MyQtProject
    main.cc
    mainwindow.cc
    parser.cc
    modelviewer.cc
)

# Линкуем проект с объединенной библиотекой gif
target_link_libraries(MyQtProject PRIVATE gif)

# Связать Qt библиотеки
target_link_libraries(MyQtProject PRIVATE
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    Qt6::Core
    Qt6::Gui
)

# Указать свойства для автоматической обработки Qt
set_target_properties(MyQtProject PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)
