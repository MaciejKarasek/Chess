add_library(Pawn)

target_precompile_headers(Pawn
    REUSE_FROM
        Piece
)

target_sources(Pawn
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Pawn.cpp
    
    PUBLIC
        FILE_SET HEADERS
        FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/Pawn.hpp
) 

target_link_libraries(Pawn
    PRIVATE
        Helpers
        Piece
)