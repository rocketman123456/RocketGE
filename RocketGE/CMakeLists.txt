message(STATUS "Add Module GEBase")
message(STATUS "###################################")
add_library( RocketGE
    src/Application.cpp
    src/EntryPoint.cpp
    src/Event.cpp
    src/Layer.cpp
    src/LayerStack.cpp
    src/Log.cpp
    src/Window.cpp
)
target_link_libraries( RocketGE PRIVATE
    ${Threads_LIBS}
    spdlog::spdlog
    spdlog::spdlog_header_only
)
if(Apple)
    target_link_libraries(RocketGE PRIVATE Platform_Apple)
elseif(Linux)
    target_link_libraries(RocketGE PRIVATE Platform_Linux)
elseif(Windows)
    target_link_libraries(RocketGE PRIVATE Platform_Windows)
endif()