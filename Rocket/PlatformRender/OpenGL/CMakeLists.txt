message(STATUS "Add Module OpenGL")
message(STATUS "###################################")
add_library( Render_OpenGL
    GERender/OpenGLContext.cpp
    GERender/OpenGLFrameBuffer.cpp
    GERender/OpenGLShader.cpp
    GERender/OpenGLIndexBuffer.cpp 
    GERender/OpenGLInstanceBuffer.cpp
    GERender/OpenGLVertexBuffer.cpp
    GERender/OpenGLVertexArray.cpp
    GERender/OpenGLRenderAPI.cpp
    GERender/OpenGLTexture2D.cpp
)
target_link_libraries( Render_OpenGL PRIVATE
    glfw Eigen3::Eigen
)