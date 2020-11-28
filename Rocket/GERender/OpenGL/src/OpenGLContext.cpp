#include "GERender/OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Rocket {
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        RK_CORE_ASSERT(m_WindowHandle, "Window handle is null!");
    }
    
    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RK_CORE_ASSERT(status, "Failed to Initialize GLAD");

        RK_CORE_INFO("OpenGL Info:");
		RK_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		RK_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		RK_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}
