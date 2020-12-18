message(STATUS "Add Module Vulkan")
message(STATUS "###################################")
add_library( Render_Vulkan
    GERender/VulkanContext.cpp
)
target_link_libraries( Render_Vulkan PRIVATE
    glfw Eigen3::Eigen
)
if(Apple)
    find_package(Vulkan REQUIRED)
elseif(Linux)
    find_package(Vulkan REQUIRED)
elseif(Windows)
    find_package(Vulkan REQUIRED)
endif()
target_include_directories( Render_Vulkan
    ${Vulkan_INCLUDE_DIRS}
)
target_link_libraries( Render_Vulkan
    ${Vulkan_LIBRARIES}
)