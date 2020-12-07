#pragma once
#include "RKEngine.h"

namespace Rocket {
    class PianoLayer : implements Layer
    {
    public:
        PianoLayer() : Layer("PianoLayer") {}
        virtual ~PianoLayer() = default;

        virtual void OnUpdate(Timestep ts) override;
        virtual void OnEvent(Event &event) override;

    private:
        bool OnPianoPlay(KeyPressedEvent& e);
    };
}