add_executable( Sandbox2D
    Sandbox2D.cpp
)
target_link_libraries( Sandbox2D PRIVATE
    GECore GELayer GERender GEModule GEWindow GECommon
    ${Threads_LIBS} Eigen3::Eigen
    spdlog imgui glad glfw yaml-cpp stb_image
)

if(Apple)
    target_link_libraries(Sandbox2D PRIVATE Platform_Apple)
elseif(Linux)
    target_link_libraries(Sandbox2D PRIVATE Platform_Linux)
elseif(Windows)
    target_link_libraries(Sandbox2D PRIVATE Platform_Windows)
endif()

if(OpenGL)
    target_link_libraries(Sandbox2D PRIVATE Render_OpenGL)
elseif(Vulkan)
    target_link_libraries(Sandbox2D PRIVATE Render_Vulkan)
elseif(Metal)
    target_link_libraries(Sandbox2D PRIVATE Render_Metal)
endif()