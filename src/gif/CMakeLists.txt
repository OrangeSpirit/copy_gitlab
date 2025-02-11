cmake_minimum_required(VERSION 3.10)
project(GifLibrary)

set(CMAKE_CXX_STANDARD 17)

#add_compile_options(-Wall -Wextra -Werror)

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

set(HEADERS
    gif_hash.h
    gif_lib.h
    gif_lib_private.h
    qgifglobal.h
    qgifimage.h
    qgifimage_p.h
)

add_library(gif STATIC ${SOURCES})

find_package(Qt6 REQUIRED COMPONENTS Core Gui)
target_link_libraries(gif PRIVATE Qt6::Core Qt6::Gui)

target_include_directories(gif PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(gif PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS gif
    ARCHIVE DESTINATION lib
)

install(FILES ${HEADERS} DESTINATION include)
