message(STATUS "Add Module OpenGL")
message(STATUS "###################################")
add_library( Render_OpenGL
    src/GERender/OpenGLContext.cpp
    src/GERender/OpenGLShader.cpp
    src/GERender/OpenGLIndexBuffer.cpp 
    src/GERender/OpenGLInstanceBuffer.cpp
    src/GERender/OpenGLVertexBuffer.cpp
    src/GERender/OpenGLVertexArray.cpp
    src/GERender/OpenGLRenderAPI.cpp
    src/GERender/OpenGLTexture2D.cpp
)
target_link_libraries( Render_OpenGL PRIVATE
    glfw Eigen3::Eigen
)