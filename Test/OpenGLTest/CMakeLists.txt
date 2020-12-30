message(STATUS "Add Module OpenGLTest")
message(STATUS "###################################")
#include_directories( . )

add_executable( triangle_01 triangle_01.cpp )
target_link_libraries( triangle_01
    spdlog imgui glad glfw stb_image
)

add_executable( simple_light simple_light.cpp )
target_link_libraries( simple_light
    spdlog imgui glad glfw stb_image
)

add_executable( simple_light_cube simple_light_cube.cpp )
target_link_libraries( simple_light_cube
    spdlog imgui glad glfw stb_image
)

add_executable( draw_cube draw_cube.cpp )
target_link_libraries( draw_cube
    spdlog imgui glad glfw stb_image
)

add_executable( instance_draw_fast instance_draw_fast.cpp )
target_link_libraries( instance_draw_fast
    spdlog imgui glad glfw stb_image
)

add_executable( stencil_testing stencil_testing.cpp )
target_link_libraries( stencil_testing
    spdlog imgui glad glfw stb_image
)