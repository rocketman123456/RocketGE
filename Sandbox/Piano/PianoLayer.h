#pragma once
#include "RKEngine.h"
#include "PlayList.h"

namespace Rocket {
    class PianoLayer : implements Layer
    {
    public:
        PianoLayer() : Layer("PianoLayer") {}
        virtual ~PianoLayer() = default;

        virtual void OnAttach() override;
		virtual void OnDetach() override {}

        virtual void OnUpdate(Timestep ts) override;
        virtual void OnEvent(Event &event) override;
        virtual void OnGuiRender() override;

    private:
        bool OnPianoPlay(KeyPressedEvent& e);
        bool OnPianoPlay(AudioEvent& e);

        Ref<PlayList> m_PlayList;
        thread_pool m_TP;
    };
}