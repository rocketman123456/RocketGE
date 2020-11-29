message(STATUS "Add Module OpenGLTest")
message(STATUS "###################################")

include_directories(
    .
)
add_executable( OpenGLTest3-3
    OpenGLTest3.3.cpp
)
target_link_libraries( OpenGLTest3-3
    spdlog imgui glad glfw stb_image
)