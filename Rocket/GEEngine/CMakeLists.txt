message(STATUS "Add Module GECore")
message(STATUS "###################################")
add_library( GEEngine
    # GECore
    src/GECore/EntryPoint.cpp
    src/GECore/Log.cpp
    src/GECore/GLFWInput.cpp
    # GECommon
    src/GECommon/OrthographicCameraController.cpp
    src/GECommon/PerspectiveCameraController.cpp
    # GEModule
    src/GEModule/Application.cpp
    src/GEModule/BaseApplication.cpp
    # GEWindow
    src/GEWindow/Window.cpp
    # GELayer
    src/GELayer/Layer.cpp
    src/GELayer/LayerStack.cpp
    src/GELayer/ImGuiBuild.cpp
    src/GELayer/ImGuiLayer.cpp
    # GERender
    src/GERender/Buffer.cpp
    src/GERender/Camera.cpp
    src/GERender/GraphicsContext.cpp
    src/GERender/RenderAPI.cpp
    src/GERender/Renderer.cpp
    src/GERender/RenderCommand.cpp
    src/GERender/Shader.cpp
    src/GERender/VertexArray.cpp
    src/GERender/OrthographicCamera.cpp
    src/GERender/PerspectiveCamera.cpp
    src/GERender/Texture.cpp
    # GERender2D
    src/GERender2D/Renderer2D.cpp
)
target_link_libraries( GEEngine PRIVATE
    glfw Eigen3::Eigen
)
