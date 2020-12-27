message(STATUS "Add Module Apple")
message(STATUS "###################################")
add_library( Platform_Apple
    GEWindow/WindowApple.cpp
    GEUtils/PlatformUtils.cpp
)
target_link_libraries( Platform_Apple PRIVATE
    glfw Eigen3::Eigen
)