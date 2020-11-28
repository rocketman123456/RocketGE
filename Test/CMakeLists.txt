message(STATUS "Add Module Test")
message(STATUS "###################################")
if(Apple)
    set(Vulkan_LIBRARIES /Users/developer/Program/CppCode/MoltenVK/MoltenVK/dylib/macOS/libMoltenVK.dylib)
    set(Vulkan_INCLUDE_DIRS /Users/developer/Program/CppCode/MoltenVK/MoltenVK/include)
elseif(Linux)
    find_package(Vulkan REQUIRED)
elseif(Windows)
    find_package(Vulkan REQUIRED)
endif()

add_executable( VulkanTest
    VulkanTest/VulkanTest.cpp
)
target_include_directories( VulkanTest PRIVATE
    ${Vulkan_INCLUDE_DIRS}
)
target_link_libraries( VulkanTest
    ${Vulkan_LIBRARIES} glfw
)

add_executable( OpenGLTest
    OpenGLTest/OpenGLTest.cpp
)
target_include_directories( OpenGLTest PRIVATE
    OpenGLTest
)
target_link_libraries( OpenGLTest
    spdlog imgui glad glfw stb_image
)