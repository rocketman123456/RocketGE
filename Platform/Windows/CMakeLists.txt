message(STATUS "Add Module Windows")
message(STATUS "###################################")
add_library( Platform_Windows
    src/WindowWindows.cpp
)
target_link_libraries( Platform_Apple
    glfw glad
)
