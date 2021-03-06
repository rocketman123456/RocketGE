#pragma once
#include "GERender/GraphicsContext.h"

struct GLFWwindow;

namespace Rocket
{
    class OpenGLContext : implements GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow *windowHandle);
        virtual ~OpenGLContext() = default;

        virtual void Init() override;
        virtual void Destory() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow *m_WindowHandle;
    };
} // namespace Rocket