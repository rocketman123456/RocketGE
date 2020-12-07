#pragma once

#include "GEEvent/Event.h"

namespace Rocket {
    class WindowResizeEvent : implements Event
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height, float x, float y)
			: m_Width(width), m_Height(height), m_xScale(x), m_yScale(y) {}

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }
		float GetXScale() const { return m_xScale; }
		float GetYScale() const { return m_yScale; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		uint32_t m_Width, m_Height;
		float m_xScale, m_yScale;
	};

    class WindowCloseEvent : implements Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppTickEvent : implements Event
	{
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppUpdateEvent : implements Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppRenderEvent : implements Event
	{
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}
