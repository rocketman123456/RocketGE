#pragma once
#include "GERender/GraphicsContext.h"

struct GLFWwindow;

namespace Rocket {
    class VulkanContext : public GraphicsContext
    {
    public:
        VulkanContext(GLFWwindow* windowHandle);
        virtual ~VulkanContext() = default;

        virtual void Init() override;
		virtual void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };
}