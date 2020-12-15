#include "PianoLayer.h"
#include <imgui.h>

static std::string A0_1 = "Piano.ff.C2";
static std::string A1_1 = "Piano.ff.D2";
static std::string A2_1 = "Piano.ff.E2";
static std::string A3_1 = "Piano.ff.F2";
static std::string A4_1 = "Piano.ff.G2";
static std::string A5_1 = "Piano.ff.A2";
static std::string A6_1 = "Piano.ff.B2";
//std::string A7_1 = "Piano.ff.C3";

static std::string A0 = "Piano.ff.C3"; // 1
static std::string A1 = "Piano.ff.D3"; // 2
static std::string A2 = "Piano.ff.E3"; // 3
static std::string A3 = "Piano.ff.F3"; // 4
static std::string A4 = "Piano.ff.G3"; // 5
static std::string A5 = "Piano.ff.A3"; // 6
static std::string A6 = "Piano.ff.B3"; // 7
static std::string A7 = "Piano.ff.C4"; // 1.

//std::string A0_2 = "Piano.ff.C4";
static std::string A1_2 = "Piano.ff.D4";
static std::string A2_2 = "Piano.ff.E4";
static std::string A3_2 = "Piano.ff.F4";
static std::string A4_2 = "Piano.ff.G4";
static std::string A5_2 = "Piano.ff.A4";
static std::string A6_2 = "Piano.ff.B4";
static std::string A7_2 = "Piano.ff.C5";

static std::string A1_3 = "Piano.ff.D5";
static std::string A2_3 = "Piano.ff.E5";
static std::string A3_3 = "Piano.ff.F5";
static std::string A4_3 = "Piano.ff.G5";
static std::string A5_3 = "Piano.ff.A5";
static std::string A6_3 = "Piano.ff.B5";
static std::string A7_3 = "Piano.ff.C6";

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
        dispatcher.Dispatch<AudioEvent>(RK_BIND_EVENT_FN(PianoLayer::OnPianoPlay));
    }

    void PianoLayer::OnGuiRender()
    {
    }

    void PianoLayer::OnAttach()
    {
        std::string path = ProjectSourceDir + "/Assets/scripts/play_list.yaml";
        m_PlayList = CreateRef<PlayList>(path, 0.5f);
    }

    bool PianoLayer::OnPianoPlay(AudioEvent& e)
    {
        g_AudioManager->PlayAudio(e.GetAudioName());
        return true;
    }

    bool PianoLayer::OnPianoPlay(KeyPressedEvent& e)
    {
        switch(e.GetKeyCode())
        {
            case Key::Q: g_AudioManager->PlayAudio(A0_1); break;
            case Key::W: g_AudioManager->PlayAudio(A1_1); break;
            case Key::E: g_AudioManager->PlayAudio(A2_1); break;
            case Key::R: g_AudioManager->PlayAudio(A3_1); break;
            case Key::T: g_AudioManager->PlayAudio(A4_1); break;
            case Key::Y: g_AudioManager->PlayAudio(A5_1); break;
            case Key::U: g_AudioManager->PlayAudio(A6_1); break;
            //case Key::I: g_AudioManager->PlayAudio(A7_1); break;

            case Key::D1: g_AudioManager->PlayAudio(A0); break;
            case Key::D2: g_AudioManager->PlayAudio(A1); break;
            case Key::D3: g_AudioManager->PlayAudio(A2); break;
            case Key::D4: g_AudioManager->PlayAudio(A3); break;
            case Key::D5: g_AudioManager->PlayAudio(A4); break;
            case Key::D6: g_AudioManager->PlayAudio(A5); break;
            case Key::D7: g_AudioManager->PlayAudio(A6); break;
            case Key::D8: g_AudioManager->PlayAudio(A7); break;

            //case Key::D1: g_AudioManager->PlayAudio(A0_2); break;
            case Key::A: g_AudioManager->PlayAudio(A1_2); break;
            case Key::S: g_AudioManager->PlayAudio(A2_2); break;
            case Key::D: g_AudioManager->PlayAudio(A3_2); break;
            case Key::F: g_AudioManager->PlayAudio(A4_2); break;
            case Key::G: g_AudioManager->PlayAudio(A5_2); break;
            case Key::H: g_AudioManager->PlayAudio(A6_2); break;
            case Key::J: g_AudioManager->PlayAudio(A7_2); break;

            case Key::Z: g_AudioManager->PlayAudio(A1_3); break;
            case Key::X: g_AudioManager->PlayAudio(A2_3); break;
            case Key::C: g_AudioManager->PlayAudio(A3_3); break;
            case Key::V: g_AudioManager->PlayAudio(A4_3); break;
            case Key::B: g_AudioManager->PlayAudio(A5_3); break;
            case Key::N: g_AudioManager->PlayAudio(A6_3); break;
            case Key::M: g_AudioManager->PlayAudio(A7_3); break;

            case Key::Space: m_TP.enqueue_work(&PlayList::Play,m_PlayList, "tiger"); break;
        }
        return false;
    }
}