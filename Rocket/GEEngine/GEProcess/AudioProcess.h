#pragma once
#include "GEProcess/Process.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

namespace Rocket {
    class AudioProcess : implements Process
    {
    public:
        AudioProcess(ALuint buffer, int volume = 100, bool looping = false);
        virtual ~AudioProcess() { alDeleteSources(1, &m_Source); }
    protected:
        virtual void OnInit(void) override;
        virtual void OnUpdate(unsigned long deltaMs) override;
        virtual void OnAbort(void) override;
    public:
        void InitializeVolume();
        void Play(const int volume, const bool looping);
        bool IsPlaying();
        void SetVolume(int vol);

        void Stop() { alSourceStop(m_Source); }
        void PauseSound() { alSourcePause(m_Source); }
        int GetVolume() { return m_Volume; }
        float GetProgress() { alGetSourcef(m_Source, AL_SEC_OFFSET, &m_Progress); return m_Progress; }
    private:
        ALuint m_Buffer;
        ALuint m_Source;
        ALenum m_State;
        ALfloat m_Progress;
        int m_Volume;
        // TODO : set audio position, to make a 3D sound
        bool m_Looping;
    };

    class FadeProcess : public Process
    {
    protected:
        Ref<AudioProcess> m_Sound;
        
        int m_TotalFadeTime;
        int m_ElapsedTime;
        int m_StartVolume;
        int m_EndVolume;

    public:
        FadeProcess(Ref<AudioProcess> sound, int fadeTime, int endVolume);
        virtual void OnUpdate(unsigned long deltaMs);
    };
}