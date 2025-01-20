# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Создаем общую библиотеку для giflib и gifimage
add_library(gif
    3rdParty/giflib/dgif_lib.c
    3rdParty/giflib/egif_lib.c
    3rdParty/giflib/gif_err.c
    3rdParty/giflib/gif_font.c
    3rdParty/giflib/gif_hash.c
    3rdParty/giflib/gifalloc.c
    3rdParty/giflib/quantize.c
    gifimage/qgifimage.cpp
)

# Указываем заголовочные файлы для общей библиотеки
target_include_directories(gif PUBLIC
    3rdParty/giflib  # Для заголовков giflib
    gifimage          # Для заголовков gifimage
)

target_compile_definitions(gif
    PRIVATE GIFIMAGE_NO_LIB
)

# Линкуем с Qt
find_package(Qt6 COMPONENTS Core Gui REQUIRED)
target_link_libraries(gif PRIVATE Qt6::Core Qt6::Gui)

# Устанавливаем CXX компилятор для библиотеки
set_target_properties(gif PROPERTIES LINKER_LANGUAGE CXX)

# Опционально добавим свойства для обработки Qt (если необходимо)
set_target_properties(gif PROPERTIES AUTOMOC ON)
