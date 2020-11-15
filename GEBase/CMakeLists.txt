add_library( GEBase
    src/Application.cpp
    src/EntryPoint.cpp
    src/Log.cpp
)
target_link_libraries( GEBase
    spdlog::spdlog
    ${Threads_LIBS}
)