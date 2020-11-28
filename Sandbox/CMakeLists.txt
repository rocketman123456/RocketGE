message(STATUS "Add Module Sandbox")
message(STATUS "###################################")
add_executable( SandboxApp
    src/SandboxApp.cpp
)
target_link_libraries( SandboxApp PRIVATE
    GECore GELayer GERender GEApplication GEWindow GECommon
)

if(Apple)
    target_link_libraries(SandboxApp PRIVATE Platform_Apple)
elseif(Linux)
    target_link_libraries(SandboxApp PRIVATE Platform_Linux)
elseif(Windows)
    target_link_libraries(SandboxApp PRIVATE Platform_Windows)
endif()

if(OpenGL)
    target_link_libraries(SandboxApp PRIVATE Render_OpenGL)
elseif(Vulkan)
    target_link_libraries(SandboxApp PRIVATE Render_Vulkan)
elseif(Metal)
    target_link_libraries(SandboxApp PRIVATE Render_Metal)
endif()

target_link_libraries( SandboxApp PRIVATE
    ${Threads_LIBS} Eigen3::Eigen
    spdlog imgui glad glfw yaml-cpp stb_image
)