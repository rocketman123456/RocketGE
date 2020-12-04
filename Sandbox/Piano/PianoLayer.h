#pragma once
#include "RKEngine.h"

namespace Rocket {
    class PianoLayer : implements Layer
    {
    public:
        PianoLayer(AudioManager* manager) : Layer("PianoLayer"), m_AudioManager(manager) {}
        virtual ~PianoLayer() = default;

        virtual void OnUpdate(Timestep ts) override;
        virtual void OnEvent(Event &event) override;

    private:
        bool OnPianoPlay(KeyPressedEvent& e);
    private:
        AudioManager* m_AudioManager;
    };
}