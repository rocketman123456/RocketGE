message(STATUS "Add Module GECore")
message(STATUS "###################################")
add_library( GEEngine
    #GEAudio
    GEAudio/Audio.cpp
    # GECore
    GECore/EntryPoint.cpp
    GECore/Log.cpp
    GECore/GLFWInput.cpp
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
    # GEWindow
    GEWindow/Window.cpp
    # GELayer
    GELayer/Layer.cpp
    GELayer/LayerStack.cpp
    GELayer/ImGuiBuild.cpp
    GELayer/ImGuiLayer.cpp
    # GEProcess
    GEProcess/Process.cpp
    # GERender
    GERender/Buffer.cpp
    GERender/GraphicsContext.cpp
    GERender/RenderAPI.cpp
    GERender/Renderer.cpp
    GERender/RenderCommand.cpp
    GERender/Shader.cpp
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

set(ENGINE_THIRD_PARTY 
    ${Threads_LIBS} ${OPENAL_LIBRARY} 
    Eigen3::Eigen spdlog glfw yaml-cpp
    OpenAL::OpenAL SndFile::sndfile
)
