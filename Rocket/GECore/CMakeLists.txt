message(STATUS "Add Module GECore")
message(STATUS "###################################")
add_library( GECore
    src/Application.cpp
    src/EntryPoint.cpp
    src/ImGuiBuild.cpp
    src/ImGuiLayer.cpp
    src/Layer.cpp
    src/LayerStack.cpp
    src/Log.cpp
    src/Window.cpp
)
target_link_libraries( GECore PRIVATE
    glfw Eigen3::Eigen
)