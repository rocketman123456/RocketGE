message(STATUS "Add Module GEBase")
message(STATUS "###################################")
add_library( RocketGE
    src/Application.cpp
    src/EntryPoint.cpp
    src/ImGuiBuild.cpp
    src/ImGuiLayer.cpp
    src/Layer.cpp
    src/LayerStack.cpp
    src/Log.cpp
    src/Window.cpp
)
target_link_libraries( RocketGE PRIVATE
    glfw Eigen3::Eigen
)