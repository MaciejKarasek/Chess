add_library(Board)

target_precompile_headers(Board
    REUSE_FROM
        Piece
)

target_sources(Board
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Board.cpp
    
    PUBLIC
        FILE_SET HEADERS
        FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/Board.hpp
)

target_link_libraries(Board
    PUBLIC
        Field
    PRIVATE
        Piece
)