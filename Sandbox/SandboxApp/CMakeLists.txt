add_executable( SandboxApp
    SandboxApp.cpp
    ExampleLayer.cpp
    ../SandboxData.cpp
)
target_include_directories( SandboxApp PRIVATE
    ${PROJECT_SOURCE_DIR}/Rocket/Interface
    ${PROJECT_SOURCE_DIR}/Sandbox/SandboxApp
    ${PROJECT_SOURCE_DIR}/Sandbox/Sandbox2D
)
target_link_libraries( SandboxApp PRIVATE
    GEEngine ${ENGINE_LIBRARY}
    ${ENGINE_PLATFORM_LIBRARY}
    ${ENGINE_RENDER_LIBRARY}
)
