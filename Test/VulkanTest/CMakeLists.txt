message(STATUS "Add Module VulkanTest")
message(STATUS "###################################")
find_package(Vulkan REQUIRED)

if(Apple)
#execute_process(COMMAND sh ${CMAKE_CURRENT_LIST_DIR}/compile-mac.sh)
endif()

add_executable( VulkanTest
    VulkanTest.cpp
)
target_include_directories( VulkanTest PRIVATE
    ${Vulkan_INCLUDE_DIRS}
)
target_link_libraries( VulkanTest
    ${Vulkan_LIBRARIES} glfw
)
