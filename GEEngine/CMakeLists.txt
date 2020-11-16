message(STATUS "Add Module GEEngine")
message(STATUS "###################################")
add_library( GEEngine
    src/Core.cpp
)
target_link_libraries( GEEngine
    spdlog::spdlog_header_only
    fmt::fmt-header-only
)