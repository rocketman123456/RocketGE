message(STATUS "Add Module GECore")
message(STATUS "###################################")
add_library( GEEngine
    #GEAudio
    src/GEAudio/Audio.cpp
    # GECore
    src/GECore/EntryPoint.cpp
    src/GECore/Log.cpp
    src/GECore/GLFWInput.cpp
    # GECommon
    src/GECommon/Camera.cpp
    src/GECommon/OrthographicCamera.cpp
    src/GECommon/PerspectiveCamera.cpp
    src/GECommon/OrthographicCameraController.cpp
    src/GECommon/PerspectiveCameraController.cpp
    # GEModule
    src/GEModule/AudioManager.cpp
    src/GEModule/Application.cpp
    src/GEModule/BaseApplication.cpp
    src/GEModule/BlockAllocator.cpp
    src/GEModule/MemoryManager.cpp
    # GEWindow
    src/GEWindow/Window.cpp
    # GELayer
    src/GELayer/Layer.cpp
    src/GELayer/LayerStack.cpp
    src/GELayer/ImGuiBuild.cpp
    src/GELayer/ImGuiLayer.cpp
    # GERender
    src/GERender/Buffer.cpp
    src/GERender/GraphicsContext.cpp
    src/GERender/RenderAPI.cpp
    src/GERender/Renderer.cpp
    src/GERender/RenderCommand.cpp
    src/GERender/Shader.cpp
    src/GERender/VertexArray.cpp
    src/GERender/Texture.cpp
    # GERender2D
    src/GERender2D/Renderer2D.cpp
    # GEUtils
    src/GEUtils/FunctionUtils.cpp
    src/GEUtils/Profile.cpp
)
target_link_libraries( GEEngine PRIVATE
    glfw Eigen3::Eigen
)

set(ENGINE_THIRD_PARTY 
    ${Threads_LIBS} ${OPENAL_LIBRARY} 
    Eigen3::Eigen spdlog glfw yaml-cpp
    OpenAL::OpenAL SndFile::sndfile
)
