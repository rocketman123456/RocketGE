message(STATUS "Add Module Linux")
message(STATUS "###################################")
add_library( Platform_Linux
    GEWindow/WindowLinux.cpp
    GEUtils/PlatformUtils.cpp
)
target_link_libraries( Platform_Linux PRIVATE
    glfw Eigen3::Eigen
)