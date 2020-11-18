message(STATUS "Add Module Apple")
message(STATUS "###################################")
add_library( Platform_Apple
    src/WindowApple.cpp
)
target_link_libraries( Platform_Apple PRIVATE
    glfw
)