add_library(Queen)

target_precompile_headers(Queen
    REUSE_FROM
        Piece
)

target_sources(Queen
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Queen.cpp
    
    PUBLIC
        FILE_SET HEADERS
        FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/Queen.hpp
) 

target_link_libraries(Queen
    PRIVATE
        Helpers
        Piece
)