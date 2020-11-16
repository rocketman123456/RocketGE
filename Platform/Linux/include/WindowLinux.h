#pragma once

#include "Core.h"
#include "GEBase/Base.h"
#include "GEWindow/Window.h"
#include "GEEvent.h"

#include <GLFW/glfw3.h>

namespace Rocket {
	class WindowLinux : public Window
	{
	public:
		WindowLinux(const WindowProps& props);
		virtual ~WindowLinux();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		virtual void* GetNativeWindow() const override { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}
