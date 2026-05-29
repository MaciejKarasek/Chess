add_library(Rook)

target_precompile_headers(Rook
    REUSE_FROM
        Piece
)

target_sources(Rook
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Rook.cpp
    
    PUBLIC
        FILE_SET HEADERS
        FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/Rook.hpp
) 

target_link_libraries(Rook
    PRIVATE
        Helpers
        Piece
)