message(STATUS "Add Module GECore")
message(STATUS "###################################")
add_library( GECore
    src/GEApplication/Application.cpp
    src/GECore/EntryPoint.cpp
    src/GECore/Log.cpp
    src/GELayer/ImGuiBuild.cpp
    src/GELayer/ImGuiLayer.cpp
    src/GELayer/Layer.cpp
    src/GELayer/LayerStack.cpp
    src/GEWindow/Window.cpp
    src/GERender/Buffer.cpp
    src/GERender/GraphicsContext.cpp
    src/GERender/RenderAPI.cpp
    src/GERender/Renderer.cpp
    src/GERender/Shader.cpp
    src/GERender/VertexArray.cpp
    src/Engine.cpp
)
target_link_libraries( GECore PRIVATE
    glfw Eigen3::Eigen
)