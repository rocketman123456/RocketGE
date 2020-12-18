message(STATUS "Add Module Windows")
message(STATUS "###################################")
add_library( Platform_Windows
    GEWindow/WindowWindows.cpp
)
target_link_libraries( Platform_Windows PRIVATE
    glfw Eigen3::Eigen
)