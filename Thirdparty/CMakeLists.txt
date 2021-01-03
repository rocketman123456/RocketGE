message(STATUS "Add Module Thirdparty")
message(STATUS "###################################")
add_subdirectory( glad )
add_subdirectory( stb_image )

add_library( imgui
    imgui/imgui.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_demo.cpp
)

add_library( crossguid
    crossguid/src/guid.cpp
)