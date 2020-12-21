message(STATUS "Add Module GEEngine")
message(STATUS "###################################")

if(Apple)
    set( Input_Method GECore/GLFWInput.cpp )
elseif(Linux)
    set( Input_Method GECore/GLFWInput.cpp )
elseif(Windows)
    set( Input_Method GECore/GLFWInput.cpp )
endif()

add_library( GEEngine
    #GEAudio
    GEAudio/Audio.cpp
    # GECore
    GECore/EntryPoint.cpp
    GECore/Log.cpp
    ${Input_Method}
    # GECommon
    GECommon/Camera.cpp
    GECommon/OrthographicCamera.cpp
    GECommon/PerspectiveCamera.cpp
    GECommon/OrthographicCameraController.cpp
    GECommon/PerspectiveCameraController.cpp
    # GEModule
    GEModule/AudioManager.cpp
    GEModule/Application.cpp
    GEModule/BaseApplication.cpp
    GEModule/BlockAllocator.cpp
    GEModule/MemoryManager.cpp
    GEModule/ProcessManager.cpp
    GEModule/WindowManager.cpp
    GEModule/EventManager.cpp
    # GEWindow
    GEWindow/Window.cpp
    # GELayer
    GELayer/Layer.cpp
    GELayer/LayerStack.cpp
    GELayer/ImGuiBuild.cpp
    GELayer/ImGuiLayer.cpp
    # GEProcess
    GEProcess/Process.cpp
    GEProcess/AudioProcess.cpp
    # GERender
    GERender/Buffer.cpp
    GERender/FrameBuffer.cpp
    GERender/GraphicsContext.cpp
    GERender/RenderAPI.cpp
    GERender/Renderer.cpp
    GERender/RenderCommand.cpp
    GERender/Shader.cpp
    GERender/SubTexture2D.cpp
    GERender/VertexArray.cpp
    GERender/Texture.cpp
    # GERender2D
    GERender2D/Renderer2D.cpp
    # GEUtils
    GEUtils/FunctionUtils.cpp
    GEUtils/Profile.cpp
)
target_link_libraries( GEEngine PRIVATE
    glfw Eigen3::Eigen
)
