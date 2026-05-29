add_library(Field)

target_precompile_headers(Field
    REUSE_FROM
        Piece
)

target_sources(Field
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Field.cpp
    PUBLIC
        FILE_SET HEADERS
        FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/Field.hpp
)

target_link_libraries(Field
    PUBLIC
        Helpers
        Piece
        Pawn
        Knight
        Bishop
        Queen
        Rook
        King
)