message(STATUS "Add Module Sandbox")
message(STATUS "###################################")
add_executable( SandboxApp
    src/SandboxApp.cpp
)
target_link_libraries( SandboxApp PRIVATE
    GEEngine
    RocketGE
)
if(Apple)
    target_link_libraries(SandboxApp PRIVATE Platform_Apple)
elseif(Linux)
    target_link_libraries(SandboxApp PRIVATE Platform_Linux)
elseif(Windows)
    target_link_libraries(SandboxApp PRIVATE Platform_Windows)
endif()
target_link_libraries( SandboxApp PRIVATE
    ${Threads_LIBS} Eigen3::Eigen
    spdlog imgui glad glfw yaml-cpp
)