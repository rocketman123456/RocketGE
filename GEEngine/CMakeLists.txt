message(STATUS "Add Module GEEngine")
message(STATUS "###################################")
add_library( GEEngine
    src/Engine.cpp
)
target_link_libraries( GEEngine
    RocketGE
)