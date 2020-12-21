add_executable( Piano
    Piano.cpp
    PianoLayer.cpp
    PlayList.cpp
)
target_include_directories( Piano PRIVATE
    ${PROJECT_SOURCE_DIR}/Rocket/Interface
    ${PROJECT_SOURCE_DIR}/Sandbox/SandboxApp
    ${PROJECT_SOURCE_DIR}/Sandbox/Sandbox2D
)
target_link_libraries( Piano PRIVATE
    GEEngine ${ENGINE_LIBRARY}
    ${ENGINE_PLATFORM_LIBRARY}
    ${ENGINE_RENDER_LIBRARY}
)
