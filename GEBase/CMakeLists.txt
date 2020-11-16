add_library( GEBase
    src/Application.cpp
    src/EntryPoint.cpp
    src/Log.cpp
)
target_link_libraries( GEBase 
    spdlog::spdlog_header_only
    fmt::fmt-header-only
    ${Threads_LIBS}
)
