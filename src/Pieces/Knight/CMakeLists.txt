add_library(Knight)

target_precompile_headers(Knight
    REUSE_FROM
        Piece
)

target_sources(Knight
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Knight.cpp
    
    PUBLIC
        FILE_SET HEADERS
        FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/Knight.hpp
) 

target_link_libraries(Knight
    PRIVATE
        Helpers
        Piece
)