message(STATUS "Add Module Vulkan")
message(STATUS "###################################")
add_library( Render_Vulkan
    GERender/VulkanContext.cpp
)
target_link_libraries( Render_Vulkan PRIVATE
    glfw Eigen3::Eigen
)

find_package(Vulkan REQUIRED)
find_package(volk CONFIG REQUIRED)

target_include_directories( Render_Vulkan
    ${Vulkan_INCLUDE_DIRS}
)
target_link_libraries( Render_Vulkan
    ${Vulkan_LIBRARIES}
    volk::volk volk::volk_headers
)