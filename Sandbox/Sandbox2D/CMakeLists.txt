add_executable( Sandbox2D
    Sandbox2D.cpp
    ../SandboxData.cpp
    ParticleSystem.cpp
    Random.cpp
)
target_include_directories( Sandbox2D PRIVATE
    ${PROJECT_SOURCE_DIR}/Rocket/Interface
    ${PROJECT_SOURCE_DIR}/Sandbox/SandboxApp
    ${PROJECT_SOURCE_DIR}/Sandbox/Sandbox2D
)
target_link_libraries( Sandbox2D PRIVATE
    GEEngine ${ENGINE_LIBRARY}
    ${ENGINE_PLATFORM_LIBRARY}
    ${ENGINE_RENDER_LIBRARY}
)
