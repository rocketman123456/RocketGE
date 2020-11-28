message(STATUS "Add Module GECore")
message(STATUS "###################################")
add_library( GECore
    src/GECore/EntryPoint.cpp
    src/GECore/Log.cpp
    src/GECore/GLFWInput.cpp
)
add_library( GECommon
    src/GECommon/OrthographicCameraController.cpp
    src/GECommon/PerspectiveCameraController.cpp
)
add_library( GEApplication
    src/GEApplication/Application.cpp
)
add_library( GEWindow
    src/GEWindow/Window.cpp
)
add_library( GELayer
    src/GELayer/Layer.cpp
    src/GELayer/LayerStack.cpp
    src/GELayer/ImGuiBuild.cpp
    src/GELayer/ImGuiLayer.cpp
)
add_library( GERender
    src/GERender/Buffer.cpp
    src/GERender/GraphicsContext.cpp
    src/GERender/RenderAPI.cpp
    src/GERender/Renderer.cpp
    src/GERender/RenderCommand.cpp
    src/GERender/Shader.cpp
    src/GERender/VertexArray.cpp
    src/GERender/OrthographicCamera.cpp
    src/GERender/PerspectiveCamera.cpp
    src/GERender/Texture.cpp
)
target_link_libraries( GECore PRIVATE
    glfw Eigen3::Eigen
)
target_link_libraries( GELayer PRIVATE
    glfw Eigen3::Eigen
)
target_link_libraries( GERender PRIVATE
    glfw Eigen3::Eigen
)
target_link_libraries( GEWindow PRIVATE
    glfw Eigen3::Eigen
)
