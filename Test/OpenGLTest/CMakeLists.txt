message(STATUS "Add Module OpenGLTest")
message(STATUS "###################################")
#include_directories( . )

add_executable( triangle_01 triangle_01.cpp )
target_link_libraries( triangle_01
    spdlog::spdlog imgui glad glfw stb_image
)

add_executable( simple_light simple_light.cpp )
target_link_libraries( simple_light
    spdlog::spdlog imgui glad glfw stb_image
)

add_executable( simple_light_cube simple_light_cube.cpp )
target_link_libraries( simple_light_cube
    spdlog::spdlog imgui glad glfw stb_image
)

add_executable( draw_cube draw_cube.cpp )
target_link_libraries( draw_cube
    spdlog::spdlog imgui glad glfw stb_image
)

add_executable( instance_draw_square instance_draw_square.cpp )
target_link_libraries( instance_draw_square
    spdlog::spdlog imgui glad glfw stb_image
)

add_executable( framebuffers framebuffers.cpp )
target_link_libraries( framebuffers
    spdlog::spdlog imgui glad glfw stb_image
)

add_executable( stencil_testing stencil_testing.cpp )
target_link_libraries( stencil_testing
    spdlog::spdlog imgui glad glfw stb_image
)