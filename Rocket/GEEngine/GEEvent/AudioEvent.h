#pragma once
#include "GEEvent/Event.h"

namespace Rocket
{
	class AudioEvent : implements Event
	{
	public:
		AudioEvent(const std::string &name)
			: m_Name(name) {}
		const std::string &GetAudioName() const { return m_Name; }

		EVENT_CLASS_CATEGORY(EventCategoryAudio)
		EVENT_CLASS_TYPE(AudioEvent)
	private:
		std::string m_Name;
	};
} // namespace Rocket