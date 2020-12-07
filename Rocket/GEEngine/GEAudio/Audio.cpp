#include "GEAudio/Audio.h"

namespace Rocket {
    void Audio::Play()
    {
        m_Playing = true;
        alSourcePlay(m_Source);
        do {
            std::this_thread::sleep_for(std::chrono::microseconds(100));
            alGetSourcei(m_Source, AL_SOURCE_STATE, &m_State);
            // Get the source offset.
            alGetSourcef(m_Source, AL_SEC_OFFSET, &m_Offset);
        } while(alGetError() == AL_NO_ERROR && m_State == AL_PLAYING);
        m_Playing = false;
    }
}