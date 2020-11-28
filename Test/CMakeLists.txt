message(STATUS "Add Module Test")
message(STATUS "###################################")
add_executable( VulkanTest
    src/VulkanTest.cpp
)
if(Apple)
    set(Vulkan_LIBRARIES /Users/developer/Program/CppCode/MoltenVK/MoltenVK/dylib/macOS/libMoltenVK.dylib)
    set(Vulkan_INCLUDE_DIRS /Users/developer/Program/CppCode/MoltenVK/MoltenVK/include)
elseif(Linux)
    find_package(Vulkan REQUIRED)
elseif(Windows)
    find_package(Vulkan REQUIRED)
endif()
include_directories( VulkanTest
    ${Vulkan_INCLUDE_DIRS}
)
target_link_libraries( VulkanTest
    ${Vulkan_LIBRARIES} glfw
)