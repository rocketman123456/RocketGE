add_executable( HazelDash
    HazelDashApp.cpp
    HazelDashLayer.cpp
    ViewPort.cpp
    Random.cpp
)
target_include_directories( HazelDash PRIVATE
    ${PROJECT_SOURCE_DIR}/Rocket/Interface
    ${PROJECT_SOURCE_DIR}/Sandbox/SandboxApp
    ${PROJECT_SOURCE_DIR}/Sandbox/Sandbox2D
    ${PROJECT_SOURCE_DIR}/Sandbox/HazelDash
)
target_link_libraries( HazelDash PRIVATE
    GEEngine ${ENGINE_LIBRARY}
    ${ENGINE_PLATFORM_LIBRARY}
    ${ENGINE_RENDER_LIBRARY}
)

if(Apple)
    target_link_libraries(HazelDash PRIVATE Platform_Apple)
elseif(Linux)
    target_link_libraries(HazelDash PRIVATE Platform_Linux)
elseif(Windows)
    target_link_libraries(HazelDash PRIVATE Platform_Windows)
endif()

if(OpenGL)
    target_link_libraries(HazelDash PRIVATE Render_OpenGL)
elseif(Vulkan)
    target_link_libraries(HazelDash PRIVATE Render_Vulkan)
elseif(Metal)
    target_link_libraries(HazelDash PRIVATE Render_Metal)
endif()