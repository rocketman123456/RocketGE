#include "GEWindow/WindowApple.h"
#include "GEEvent/KeyEvent.h"
#include "GEEvent/MouseEvent.h"
#include "GEEvent/ApplicationEvent.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#ifdef RK_OPENGL
#include "GERender/OpenGLContext.h"
#endif
#ifdef RK_VULKAN
#include "GERender/VulkanContext.h"
#endif
#ifdef RK_METAL
#include "GERender/MetalContext.h"
#endif

namespace Rocket
{
	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char *description)
	{
		RK_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	WindowApple::WindowApple(const WindowProps &props)
	{
		RK_PROFILE_FUNCTION();
		Init(props);
	}

	WindowApple::~WindowApple()
	{
		RK_PROFILE_FUNCTION();
		Shutdown();
	}

	void WindowApple::Init(const WindowProps &props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		RK_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (s_GLFWWindowCount == 0)
		{
			int success = glfwInit();
			RK_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		{
#if defined(RK_OPENGL)
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#elif defined(RK_VULKAN)
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#elif defined(RK_METAL)
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#endif
			glfwWindowHint(GLFW_SCALE_TO_MONITOR, GL_TRUE);
#if defined(RK_DEBUG)
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif
			//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

			m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
			++s_GLFWWindowCount;
		}

		m_Context = GraphicsContext::Create(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
			//RK_CORE_TRACE("glfwSetWindowSizeCallback");
		});

		glfwSetWindowContentScaleCallback(m_Window, [](GLFWwindow* window, float xscale, float yscale){
			RK_CORE_TRACE("glfwSetWindowContentScaleCallback");
		});

		glfwSetWindowRefreshCallback(m_Window, [](GLFWwindow* window){
			RK_CORE_TRACE("glfwSetWindowRefreshCallback");
			//glfwSwapBuffers(window);
		});

		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height){
			WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height, 1.0f, 1.0f);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
			WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
			WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS: {
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE: {
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT: {
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int keycode) {
			WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods) {
			WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS: {
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE: {
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset, double yOffset) {
			WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos) {
			WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	void WindowApple::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void WindowApple::PollEvent()
	{
		glfwPollEvents();
	}

	void WindowApple::OnUpdate()
	{
		RK_PROFILE_FUNCTION();
		m_Context->SwapBuffers();
	}

	void WindowApple::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowApple::IsVSync() const
	{
		return m_Data.VSync;
	}
}
