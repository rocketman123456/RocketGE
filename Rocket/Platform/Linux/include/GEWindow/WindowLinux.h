#pragma once

#include "GECore/Core.h"
#include "GEWindow/Window.h"
#include "GEEvent/Event.h"
#include "GERender/GraphicsContext.h"

struct GLFWwindow;

namespace Rocket {
	class WindowLinux : implements Window
	{
	public:
		WindowLinux(const WindowProps& props);
		virtual ~WindowLinux();

		virtual void PollEvent() override;
		virtual void OnUpdate() override;

		uint32_t GetWidth() const override { return m_Data.Width; }
		uint32_t GetHeight() const override { return m_Data.Height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		virtual void* GetNativeWindow() const override { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
		GLFWwindow *m_Window;
		GraphicsContext *m_Context;
	};

}
