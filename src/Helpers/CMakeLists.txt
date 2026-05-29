add_library(Helpers)

target_precompile_headers(Helpers
    PUBLIC
        Coords.hpp
)

target_sources(Helpers
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Coords.cpp
)