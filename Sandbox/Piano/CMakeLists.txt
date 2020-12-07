add_executable( Piano
    Piano.cpp
    PianoLayer.cpp
)
target_include_directories( Piano PRIVATE
    ${PROJECT_SOURCE_DIR}/Rocket/Interface
    ${PROJECT_SOURCE_DIR}/Sandbox/SandboxApp
    ${PROJECT_SOURCE_DIR}/Sandbox/Sandbox2D
)
target_link_libraries( Piano PRIVATE
    GEEngine imgui glad stb_image ${ENGINE_THIRD_PARTY}
    OpenAL::OpenAL SndFile::sndfile Eigen3::Eigen
)

if(Apple)
    target_link_libraries(Piano PRIVATE Platform_Apple)
elseif(Linux)
    target_link_libraries(Piano PRIVATE Platform_Linux)
elseif(Windows)
    target_link_libraries(Piano PRIVATE Platform_Windows)
endif()

if(OpenGL)
    target_link_libraries(Piano PRIVATE Render_OpenGL)
elseif(Vulkan)
    target_link_libraries(Piano PRIVATE Render_Vulkan)
elseif(Metal)
    target_link_libraries(Piano PRIVATE Render_Metal)
endif()