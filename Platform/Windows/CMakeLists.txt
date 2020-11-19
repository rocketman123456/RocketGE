message(STATUS "Add Module Windows")
message(STATUS "###################################")
add_library( Platform_Windows
    src/WindowWindows.cpp
    src/InputWindows.cpp
)
target_link_libraries( Platform_Windows PRIVATE
    glfw Eigen3::Eigen
)