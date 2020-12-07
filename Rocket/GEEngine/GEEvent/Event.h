#pragma once

#include "GECore/Core.h"

class manual_event
{
public:
	explicit manual_event(bool signaled = false)
	: m_signaled(signaled) {}

	void signal()
	{
		{
			std::unique_lock lock(m_mutex);
			m_signaled = true;
		}
		m_cv.notify_all();
	}

	void wait()
	{
		std::unique_lock lock(m_mutex);
		m_cv.wait(lock, [&]() { return m_signaled != false; });
	}

	template<typename Rep, typename Period>
	bool wait_for(const std::chrono::duration<Rep, Period>& t)
	{
		std::unique_lock lock(m_mutex);
		return m_cv.wait_for(lock, t, [&]() { return m_signaled != false; });
	}

	template<typename Clock, typename Duration>
	bool wait_until(const std::chrono::time_point<Clock, Duration>& t)
	{
		std::unique_lock lock(m_mutex);
		return m_cv.wait_until(lock, t, [&]() { return m_signaled != false; });
	}

	void reset()
	{
		std::unique_lock lock(m_mutex);
		m_signaled = false;
	}

private:
	bool m_signaled = false;
	std::mutex m_mutex;
	std::condition_variable m_cv;
};

class auto_event
{
public:
	explicit auto_event(bool signaled = false)
	: m_signaled(signaled) {}

	void signal()
	{
		{
			std::unique_lock lock(m_mutex);
			m_signaled = true;
		}
		m_cv.notify_one();
	}

	void wait()
	{
		std::unique_lock lock(m_mutex);
		m_cv.wait(lock, [&]() { return m_signaled != false; });
		m_signaled = false;
	}

	template<typename Rep, typename Period>
	bool wait_for(const std::chrono::duration<Rep, Period>& t)
	{
		std::unique_lock lock(m_mutex);
		bool result = m_cv.wait_for(lock, t, [&]() { return m_signaled != false; });
		if(result) m_signaled = false;
		return result;
	}

	template<typename Clock, typename Duration>
	bool wait_until(const std::chrono::time_point<Clock, Duration>& t)
	{
		std::unique_lock lock(m_mutex);
		bool result = m_cv.wait_until(lock, t, [&]() { return m_signaled != false; });
		if(result) m_signaled = false;
		return result;
	}

private:
	bool m_signaled = false;
	std::mutex m_mutex;
	std::condition_variable m_cv;
};

namespace Rocket {

    // Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

    enum class EventType
    {
        None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		DelayedEvent,
    };

    enum EventCategory
	{
		None = 0,
		EventCategoryApplication    = BIT(0),
		EventCategoryInput          = BIT(1),
		EventCategoryKeyboard       = BIT(2),
		EventCategoryMouse          = BIT(3),
		EventCategoryMouseButton    = BIT(4),
		EventCategoryDelay		    = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return static_cast<int>(category); }

    Interface Event
	{
	public:
		virtual ~Event() = default;

		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & static_cast<int>(category);
		}
	};

    class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}
		
		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}