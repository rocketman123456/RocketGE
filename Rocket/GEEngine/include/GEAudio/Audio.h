#pragma once
#include "GECore/Core.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

namespace Rocket {
    class Audio
    {
    public:
        Audio(const std::string& name, ALuint source) : m_Name(name), m_Source(source) {}
        virtual ~Audio() = default;

        void Play();

        const std::string& GetName() { return m_Name; }
        bool IsPlaying() { return m_Playing; }
    private:
        std::string m_Name;
        ALuint m_Source;
        ALenum m_State;
        ALfloat m_Offset;
        bool m_Playing = false;
    };
}
