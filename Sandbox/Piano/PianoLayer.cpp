#include "PianoLayer.h"

namespace Rocket {
    void PianoLayer::OnUpdate(Timestep ts)
    {
        RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
        RenderCommand::Clear();
    }

    void PianoLayer::OnEvent(Event &event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<KeyPressedEvent>(RK_BIND_EVENT_FN(PianoLayer::OnPianoPlay));
    }

    bool PianoLayer::OnPianoPlay(KeyPressedEvent& e)
    {
        RK_CORE_TRACE(e);

        std::string A0 = "Piano.ff.A0";
        std::string A1 = "Piano.ff.A1";
        std::string A2 = "Piano.ff.A2";
        std::string A3 = "Piano.ff.A3";
        std::string A4 = "Piano.ff.A4";
        std::string A5 = "Piano.ff.A5";
        std::string A6 = "Piano.ff.A6";
        std::string A7 = "Piano.ff.A7";

        switch(e.GetKeyCode())
        {
            case Key::D0: m_AudioManager->PlayAudio(A0); break;
            case Key::D1: m_AudioManager->PlayAudio(A1); break;
            case Key::D2: m_AudioManager->PlayAudio(A2); break;
            case Key::D3: m_AudioManager->PlayAudio(A3); break;
            case Key::D4: m_AudioManager->PlayAudio(A4); break;
            case Key::D5: m_AudioManager->PlayAudio(A5); break;
            case Key::D6: m_AudioManager->PlayAudio(A6); break;
            case Key::D7: m_AudioManager->PlayAudio(A7); break;
        }
        return false;
    }
}