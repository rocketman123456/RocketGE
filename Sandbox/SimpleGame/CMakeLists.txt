add_executable( SimpleGame
    SimpleGame.cpp
    Random.cpp
    ParticleSystem.cpp
    Player.cpp
    Level.cpp
    GameLayer.cpp
)
target_include_directories( SimpleGame PRIVATE
    ${PROJECT_SOURCE_DIR}/Rocket/Interface
)
target_link_libraries( SimpleGame PRIVATE
    GEEngine imgui glad stb_image ${ENGINE_THIRD_PARTY}
    OpenAL::OpenAL SndFile::sndfile Eigen3::Eigen
)

if(Apple)
    target_link_libraries(SimpleGame PRIVATE Platform_Apple)
elseif(Linux)
    target_link_libraries(SimpleGame PRIVATE Platform_Linux)
elseif(Windows)
    target_link_libraries(SimpleGame PRIVATE Platform_Windows)
endif()

if(OpenGL)
    target_link_libraries(SimpleGame PRIVATE Render_OpenGL)
elseif(Vulkan)
    target_link_libraries(SimpleGame PRIVATE Render_Vulkan)
elseif(Metal)
    target_link_libraries(SimpleGame PRIVATE Render_Metal)
endif()