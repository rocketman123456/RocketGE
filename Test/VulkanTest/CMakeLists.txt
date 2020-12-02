message(STATUS "Add Module VulkanTest")
message(STATUS "###################################")
find_package(Vulkan REQUIRED)

add_executable( VulkanTest
    VulkanTest.cpp
)
target_include_directories( VulkanTest PRIVATE
    ${Vulkan_INCLUDE_DIRS}
)
target_link_libraries( VulkanTest
    ${Vulkan_LIBRARIES} glfw stb_image
    tinyobjloader
)

add_executable( VulkanLogicalDevice
    VulkanLogicalDevice.cpp
)
target_include_directories( VulkanLogicalDevice PRIVATE
    ${Vulkan_INCLUDE_DIRS}
)
target_link_libraries( VulkanLogicalDevice
    ${Vulkan_LIBRARIES} glfw
)

add_executable( VulkanInstance
    VulkanInstance.cpp
)
target_include_directories( VulkanInstance PRIVATE
    ${Vulkan_INCLUDE_DIRS}
)
target_link_libraries( VulkanInstance
    ${Vulkan_LIBRARIES} glfw
)

add_executable( VulkanPhysicsDevice
    VulkanPhysicsDevice.cpp
)
target_include_directories( VulkanPhysicsDevice PRIVATE
    ${Vulkan_INCLUDE_DIRS}
)
target_link_libraries( VulkanPhysicsDevice
    ${Vulkan_LIBRARIES} glfw
)