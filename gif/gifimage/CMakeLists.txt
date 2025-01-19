add_library(gifimage
    qgifimage.cpp
)

# Указываем директорию с заголовочными файлами для lib2
target_include_directories(gifimage
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

#add_subdirectory(../3rdParty)  # Это подключает CMakeLists.txt из lib1
add_subdirectory(../3rdParty ../build_3rdParty)

# Линкуем lib2 с lib1
target_link_libraries(gifimage
    PRIVATE giflib  # Зависимость от lib1 (giflib)
)

find_package(Qt6 COMPONENTS Core Gui REQUIRED)
target_link_libraries(gifimage PRIVATE Qt6::Core Qt6::Gui)

