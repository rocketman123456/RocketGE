#pragma once
#include "GEInterface/IRuntimeModule.h"
#include "GEAudio/Audio.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <sndfile.h>

namespace Rocket
{
    struct AudioInfo
    {
        ALuint buffer;
        ALuint source;
    };

    class AudioManager : implements IRuntimeModule
    {
    public:
        AudioManager() : IRuntimeModule("AudioManager") {}
        virtual ~AudioManager() {}

        virtual int Initialize() override;
        virtual void Finalize() override;

        virtual int Tick(Timestep ts) override;

        void LoadAudio(const std::string &filename);
        void PlayAudio(const std::string &name);

    private:
        ALuint Load(const std::string &filename);
        void Play(AudioInfo &info);

    private:
        std::unordered_map<std::string, AudioInfo> m_AudioStore;
    };

    extern AudioManager *g_AudioManager;
} // namespace Rocket