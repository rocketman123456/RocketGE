#include "GERender/VulkanContext.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Rocket {
    VulkanContext::VulkanContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        RK_CORE_ASSERT(m_WindowHandle, "Window handle is null!");
    }
    void VulkanContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
    }

    void VulkanContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}
