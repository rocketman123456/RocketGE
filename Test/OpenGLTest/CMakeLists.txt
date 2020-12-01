message(STATUS "Add Module OpenGLTest")
message(STATUS "###################################")
include_directories( . )

add_executable( OpenGLTest3.3 OpenGLTest3.3.cpp )
target_link_libraries( OpenGLTest3.3
    spdlog imgui glad glfw stb_image
)

add_executable( OpenGLTest2.2 OpenGLTest2.2.cpp )
target_link_libraries( OpenGLTest2.2
    spdlog imgui glad glfw stb_image
)

add_executable( OpenGLTest3.1 OpenGLTest3.1.cpp )
target_link_libraries( OpenGLTest3.1
    spdlog imgui glad glfw stb_image
)

add_executable( OpenGLTest4.2 OpenGLTest4.2.cpp )
target_link_libraries( OpenGLTest4.2
    spdlog imgui glad glfw stb_image
)