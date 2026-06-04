add_library(Bishop)

target_precompile_headers(Bishop
    REUSE_FROM
        Piece
)

target_sources(Bishop
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Bishop.cpp
    
    PUBLIC
        FILE_SET HEADERS
        FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/Bishop.hpp
) 

target_link_libraries(Bishop
    PRIVATE
        Helpers
        Piece
)