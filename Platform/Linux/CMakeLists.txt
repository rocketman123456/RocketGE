message(STATUS "Add Module Linux")
message(STATUS "###################################")
add_library( Platform_Linux
    src/WindowLinux.cpp
    src/InputLinux.cpp
)
target_link_libraries( Platform_Linux PRIVATE
    glfw
)