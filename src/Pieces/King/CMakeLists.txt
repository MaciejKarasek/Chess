add_library(King)

target_precompile_headers(King
    REUSE_FROM
        Piece
)

target_sources(King
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/King.cpp
    
    PUBLIC
        FILE_SET HEADERS
        FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/King.hpp
) 

target_link_libraries(King
    PRIVATE
        Helpers
        Piece
)