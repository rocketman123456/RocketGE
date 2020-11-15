include_directories( include )

add_executable(SandboxApp
    src/SandboxApp.cpp
)
target_link_libraries(SandboxApp
    GEBase
)