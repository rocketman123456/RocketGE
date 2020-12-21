#include "GEAudio/Audio.h"

namespace Rocket
{
	void Audio::Play()
	{
		m_Playing = true;
		alSourcePlay(m_Source);
		do
		{
			std::this_thread::sleep_for(std::chrono::microseconds(100));
			alGetSourcei(m_Source, AL_SOURCE_STATE, &m_State);
			// Get the source offset.
			alGetSourcef(m_Source, AL_SEC_OFFSET, &m_Offset);
		} while (alGetError() == AL_NO_ERROR && m_State == AL_PLAYING);
		m_Playing = false;
	}

	AudioSource::AudioSource(uint32_t handle, bool loaded, float length)
		: m_BufferHandle(handle), m_Loaded(loaded), m_TotalDuration(length)
	{
	}

	AudioSource::~AudioSource()
	{
		// TODO: free openal audio source?
	}

	void AudioSource::SetPosition(float x, float y, float z)
	{
		//alSource3f(source, AL_VELOCITY, 0, 0, 0);

		m_Position[0] = x;
		m_Position[1] = y;
		m_Position[2] = z;

		alSourcefv(m_SourceHandle, AL_POSITION, m_Position);
	}

	void AudioSource::SetGain(float gain)
	{
		m_Gain = gain;

		alSourcef(m_SourceHandle, AL_GAIN, gain);
	}

	void AudioSource::SetPitch(float pitch)
	{
		m_Pitch = pitch;

		alSourcef(m_SourceHandle, AL_PITCH, pitch);
	}

	void AudioSource::SetSpatial(bool spatial)
	{
		m_Spatial = spatial;

		alSourcei(m_SourceHandle, AL_SOURCE_SPATIALIZE_SOFT, spatial ? AL_TRUE : AL_FALSE);
		alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
	}

	void AudioSource::SetLoop(bool loop)
	{
		m_Loop = loop;

		alSourcei(m_SourceHandle, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
	}

	std::pair<uint32_t, uint32_t> AudioSource::GetLengthMinutesAndSeconds() const
	{
		return {(uint32_t)(m_TotalDuration / 60.0f), (uint32_t)m_TotalDuration % 60};
	}

	AudioSource AudioSource::LoadFromFile(const std::string &file, bool spatial)
	{
		AudioSource result;
		//AudioSource result = Audio::LoadAudioSource(file);
		result.SetSpatial(spatial);
		return result;
	}
} // namespace Rocket