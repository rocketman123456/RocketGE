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
    GEEngine ${ENGINE_LIBRARY}
    ${ENGINE_PLATFORM_LIBRARY}
    ${ENGINE_RENDER_LIBRARY}
)