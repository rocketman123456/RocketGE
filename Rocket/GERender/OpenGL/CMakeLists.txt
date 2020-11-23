message(STATUS "Add Module OpenGL")
message(STATUS "###################################")
add_library( Render_OpenGL
    src/OpenGLContext.cpp
    src/OpenGLShader.cpp
    src/OpenGLIndexBuffer.cpp 
    src/OpenGLVertexBuffer.cpp
    src/OpenGLVertexArray.cpp
 "include/GERender/OpenGLRenderAPI.h" "src/OpenGLRenderAPI.cpp")
target_link_libraries( Render_OpenGL PRIVATE
    glfw Eigen3::Eigen
)