#ifdef RK_OPENGL
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "examples/imgui_impl_opengl3.cpp"
#endif
#ifdef RK_VULKAN
#include "examples/imgui_impl_vulkan.cpp"
#endif
#ifdef RK_METAL
#include "examples/imgui_impl_metal.mm"
#endif
#include "examples/imgui_impl_glfw.cpp"
