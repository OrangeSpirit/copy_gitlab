cmake_minimum_required(VERSION 3.10)
project(GifLibrary)

# Установите стандарт языка C++
set(CMAKE_CXX_STANDARD 11)

# Указание всех исходных файлов
set(SOURCES
    dgif_lib.c
    egif_lib.c
    gifalloc.c
    gif_err.c
    gif_font.c
    gif_hash.c
    quantize.c
    qgifimage.cpp
)

# Указание заголовочных файлов
set(HEADERS
    gif_hash.h
    gif_lib.h
    gif_lib_private.h
    qgifglobal.h
    qgifimage.h
    qgifimage_p.h
)

# Создание статической библиотеки (расширение .a)
add_library(gif STATIC ${SOURCES})

# Подключение Qt к библиотеке (если используется Qt)
find_package(Qt6 REQUIRED COMPONENTS Core Gui)
target_link_libraries(gif PRIVATE Qt6::Core Qt6::Gui)

# Добавление директории с заголовочными файлами в include
target_include_directories(gif PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Установка выходной директории для сборки в текущую директорию
set_target_properties(gif PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Установка библиотеки и заголовочных файлов
install(TARGETS gif
    ARCHIVE DESTINATION lib
)

install(FILES ${HEADERS} DESTINATION include)
