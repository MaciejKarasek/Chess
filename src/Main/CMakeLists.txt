add_executable(Main)

target_sources(Main
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(Main
    PRIVATE
        Game
)