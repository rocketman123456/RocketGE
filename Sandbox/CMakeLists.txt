message(STATUS "Add Module Sandbox")
message(STATUS "###################################")

set( ENGINE_LIBRARY
    ${Threads_LIBS} ${OPENAL_LIBRARY} 
    ${ENGINE_PLATFORM} ${ENGINE_RENDER}
    Eigen3::Eigen spdlog glfw yaml-cpp
    OpenAL::OpenAL SndFile::sndfile EnTT::EnTT
    imgui glad stb_image
    CACHE STRING ""
)

if(Apple)
    set(ENGINE_PLATFORM_LIBRARY Platform_Apple CACHE STRING "")
elseif(Linux)
    set(ENGINE_PLATFORM_LIBRARY Platform_Linux CACHE STRING "")
elseif(Windows)
    set(ENGINE_PLATFORM_LIBRARY Platform_Windows CACHE STRING "")
endif()

if(OpenGL)
    set(ENGINE_RENDER_LIBRARY Render_OpenGL CACHE STRING "")
elseif(Vulkan)
    set(ENGINE_RENDER_LIBRARY Render_Vulkan CACHE STRING "")
elseif(Metal)
    set(ENGINE_RENDER_LIBRARY Render_Metal CACHE STRING "")
endif()

add_subdirectory( SandboxApp )
add_subdirectory( Sandbox2D )
add_subdirectory( Piano )
add_subdirectory( SimpleGame )
add_subdirectory( HazelDash )
