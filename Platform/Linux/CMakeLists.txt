message(STATUS "Add Module Linux")
message(STATUS "###################################")
add_library( Platform_Linux
    src/WindowLinux.cpp
)
target_link_libraries( Platform_Linux PRIVATE
    glfw glad
    GEBase
    GEEvent
)
