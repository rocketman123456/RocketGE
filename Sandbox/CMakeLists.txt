message(STATUS "Add Module Sandbox")
message(STATUS "###################################")
add_executable( SandboxApp
    src/SandboxApp.cpp
)
target_link_libraries( SandboxApp PRIVATE
    GEEngine
    RocketGE
)
target_link_libraries( SandboxApp PRIVATE
    ${Threads_LIBS}
    spdlog::spdlog
    spdlog::spdlog_header_only
    imgui
)