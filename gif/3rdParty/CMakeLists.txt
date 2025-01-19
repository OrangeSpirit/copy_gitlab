add_library(giflib STATIC
    giflib/dgif_lib.c
    giflib/egif_lib.c
    giflib/gif_err.c
    giflib/gif_font.c
    giflib/gif_hash.c
    giflib/gifalloc.c
    giflib/quantize.c
)

target_include_directories(giflib
    PUBLIC
        giflib/
)

set_target_properties(giflib PROPERTIES LINKER_LANGUAGE CXX)

