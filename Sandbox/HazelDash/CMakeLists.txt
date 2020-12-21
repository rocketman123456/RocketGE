add_executable( HazelDash
    ViewPort.cpp
    Random.cpp
    HazelDashLayer.cpp
    HazelDashApp.cpp
)
target_include_directories( HazelDash PRIVATE
    ${PROJECT_SOURCE_DIR}/Rocket/Interface
    ${PROJECT_SOURCE_DIR}/Sandbox/SandboxApp
    ${PROJECT_SOURCE_DIR}/Sandbox/Sandbox2D
)
target_link_libraries( HazelDash PRIVATE
    GEEngine imgui glad stb_image ${ENGINE_THIRD_PARTY}
    OpenAL::OpenAL SndFile::sndfile Eigen3::Eigen
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