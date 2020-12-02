message(STATUS "Add Module Thirdparty")
message(STATUS "###################################")
add_subdirectory( glad )
#add_subdirectory( imgui )
add_subdirectory( stb_image )
add_subdirectory( spdlog )

add_library( tinyobjloader
    tinyobjloader/tiny_obj_loader.cc
)

add_library(imgui
    imgui/imgui.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_demo.cpp
)