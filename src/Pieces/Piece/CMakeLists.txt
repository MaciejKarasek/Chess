add_library(Piece)

target_precompile_headers(Piece
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src/Helpers/Coords.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Piece.hpp
)

target_sources(Piece
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Piece.cpp
) 

target_link_libraries(Piece
    PRIVATE
        Helpers
)