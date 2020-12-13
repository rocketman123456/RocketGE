#pragma once

#include "GECore/Core.h"
#include "GEWindow/Window.h"
#include "GEEvent/Event.h"
#include "GERender/GraphicsContext.h"

struct GLFWwindow;

namespace Rocket
{
	class WindowApple : implements Window
	{
	public:
		WindowApple(const WindowProps &props);
		virtual ~WindowApple();

		virtual void PollEvent() override;
		virtual void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn &callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		virtual void *GetNativeWindow() const override { return m_Window; }

	private:
		virtual void Init(const WindowProps &props);
		virtual void Shutdown();

	private:
		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			float xScale = 1.0f, yScale = 1.0f;
			bool VSync;
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
		GLFWwindow *m_Window;
		Scope<GraphicsContext> m_Context;
	};

} // namespace Rocket