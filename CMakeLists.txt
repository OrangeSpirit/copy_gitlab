# Минимальная версия CMake и проект
cmake_minimum_required(VERSION 3.10)

project(MyQtProject VERSION 1.0 LANGUAGES CXX)

# Найти необходимые компоненты Qt
find_package(Qt6 COMPONENTS Widgets OpenGL OpenGLWidgets Core Gui REQUIRED)

# Добавляем библиотеки
# add_subdirectory(gif/3rdParty)  # Сначала добавляем lib1
add_subdirectory(gif/gifimage)  # Затем добавляем lib2


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавить исполняемый файл
add_executable(MyQtProject
    main.cc
    mainwindow.cc
    parser.cc
    modelviewer.cc
    # gif/gifimage/qgifimage.cpp  # Основной файл qtgifimage
    # gif/3rdParty/giflib/dgif_lib.c  # Файлы giflib
    # gif/3rdParty/giflib/egif_lib.c
    # gif/3rdParty/giflib/gif_err.c
    # gif/3rdParty/giflib/gif_hash.c
    # gif/3rdParty/giflib/gifalloc.c
    # gif/3rdParty/giflib/quantize.c
)

# # Пути к заголовочным файлам
# target_include_directories(MyQtProject PRIVATE
#     gif/qtgifimage           # Для заголовков qtgifimage
#     gif/3rdParty/giflib      # Для заголовков giflib
# )

# Установить определения
# target_compile_definitions(MyQtProject PRIVATE GIFIMAGE_NO_LIB)

# Связать Qt библиотеки
target_link_libraries(MyQtProject PRIVATE
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    Qt6::Core
    Qt6::Gui
)

target_link_libraries(MyQtProject PRIVATE gifimage)

# Указать свойства для автоматической обработки Qt
set_target_properties(MyQtProject PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

