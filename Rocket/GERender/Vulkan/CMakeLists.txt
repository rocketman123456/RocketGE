message(STATUS "Add Module Vulkan")
message(STATUS "###################################")
add_library( Render_Vulkan
    src/VulkanContext.cpp
)
target_link_libraries( Render_Vulkan PRIVATE
    glfw Eigen3::Eigen
)
if(Apple)
    set(Vulkan_LIBRARIES /Users/developer/Program/CppCode/MoltenVK/MoltenVK/dylib/macOS/libMoltenVK.dylib)
    set(Vulkan_INCLUDE_DIRS /Users/developer/Program/CppCode/MoltenVK/MoltenVK/include)
elseif(Linux)
    find_package(Vulkan REQUIRED)
    #set(Vulkan_LIBRARIES /home/developer/Program/Vulkan/lib/libVulkan.lib)
    #set(Vulkan_INCLUDE_DIRS /home/developer/Program/Vulkan/include)
elseif(Windows)
    find_package(Vulkan REQUIRED)
endif()
target_include_directories( Render_Vulkan
    ${Vulkan_INCLUDE_DIRS}
)
target_link_libraries( Render_Vulkan
    ${Vulkan_LIBRARIES}
)