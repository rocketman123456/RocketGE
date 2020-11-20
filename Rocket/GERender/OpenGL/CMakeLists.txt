message(STATUS "Add Module OpenGL")
message(STATUS "###################################")
add_library( Render_OpenGL
    src/OpenGL.cpp
)
target_link_libraries( Render_OpenGL PRIVATE
    glfw Eigen3::Eigen
)