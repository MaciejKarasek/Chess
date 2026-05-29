add_library(Game)

target_sources(Game
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp
    
    PUBLIC
        FILE_SET HEADERS
        FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/Game.hpp
)

target_link_libraries(Game
    PRIVATE
        Board
)
