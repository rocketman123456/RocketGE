message(STATUS "Add Module Apple")
message(STATUS "###################################")
add_library( Platform_Apple
    GEWindow/WindowApple.cpp
)
target_link_libraries( Platform_Apple PRIVATE
    glfw Eigen3::Eigen
)