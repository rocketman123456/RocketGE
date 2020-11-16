message(STATUS "Add Module Sandbox")
message(STATUS "###################################")
add_executable( SandboxApp
    src/SandboxApp.cpp
)
target_link_libraries( SandboxApp
    GEEngine
    GEBase
    GEWindow
)