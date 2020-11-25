#pragma once

#include "GECore/Core.h"
#include "GEWindow.h"
#include "GEEvent.h"
#include "GERender/GraphicsContext.h"

struct GLFWwindow;

namespace Rocket
{
	class WindowApple : public Window
	{
	public:
		WindowApple(const WindowProps &props);
		virtual ~WindowApple();

		void OnUpdate() override;

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
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
		GLFWwindow *m_Window;
		GraphicsContext *m_Context;
	};

} // namespace Rocket