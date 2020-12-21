#pragma once
#include "GECore/Core.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

namespace Rocket
{
	class Audio
	{
	public:
		Audio(const std::string &name, ALuint source) : m_Name(name), m_Source(source) {}
		virtual ~Audio() = default;

		void Play();

		const std::string &GetName() { return m_Name; }
		bool IsPlaying() { return m_Playing; }

	private:
		std::string m_Name;
		ALuint m_Source;
		ALenum m_State;
		ALfloat m_Offset;
		bool m_Playing = false;
	};

	class AudioSource
	{
	public:
		~AudioSource();

		bool IsLoaded() const { return m_Loaded; }

		void SetPosition(float x, float y, float z);
		void SetGain(float gain);
		void SetPitch(float pitch);
		void SetSpatial(bool spatial);
		void SetLoop(bool loop);

		std::pair<uint32_t, uint32_t> GetLengthMinutesAndSeconds() const;

		static AudioSource LoadFromFile(const std::string &file, bool spatial = false);

	private:
		AudioSource() = default;
		AudioSource(uint32_t handle, bool loaded, float length);

		uint32_t m_BufferHandle = 0;
		uint32_t m_SourceHandle = 0;
		bool m_Loaded = false;
		bool m_Spatial = false;

		float m_TotalDuration = 0; // in seconds

		// Attributes
		float m_Position[3] = {0.0f, 0.0f, 0.0f};
		float m_Gain = 1.0f;
		float m_Pitch = 1.0f;
		bool m_Loop = false;

		friend class Audio;
	};
} // namespace Rocket
