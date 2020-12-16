#include "Piano.h"
#include "PianoLayer.h"

static std::string A1_1 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.C1.wav";
static std::string A2_1 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.D1.wav";
static std::string A3_1 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.E1.wav";
static std::string A4_1 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.F1.wav";
static std::string A5_1 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.G1.wav";
static std::string A6_1 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.A1.wav";
static std::string A7_1 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.B1.wav";

static std::string A1_2 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.C2.wav";
static std::string A2_2 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.D2.wav";
static std::string A3_2 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.E2.wav";
static std::string A4_2 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.F2.wav";
static std::string A5_2 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.G2.wav";
static std::string A6_2 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.A2.wav";
static std::string A7_2 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.B2.wav";

static std::string A1_3 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.C3.wav";
static std::string A2_3 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.D3.wav";
static std::string A3_3 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.E3.wav";
static std::string A4_3 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.F3.wav";
static std::string A5_3 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.G3.wav";
static std::string A6_3 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.A3.wav";
static std::string A7_3 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.B3.wav";

static std::string A1_4 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.C4.wav";
static std::string A2_4 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.D4.wav";
static std::string A3_4 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.E4.wav";
static std::string A4_4 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.F4.wav";
static std::string A5_4 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.G4.wav";
static std::string A6_4 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.A4.wav";
static std::string A7_4 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.B4.wav";

static std::string A1_5 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.C5.wav";
static std::string A2_5 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.D5.wav";
static std::string A3_5 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.E5.wav";
static std::string A4_5 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.F5.wav";
static std::string A5_5 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.G5.wav";
static std::string A6_5 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.A5.wav";
static std::string A7_5 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.B5.wav";

static std::string A1_6 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.C6.wav";
static std::string A2_6 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.D6.wav";
static std::string A3_6 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.E6.wav";
static std::string A4_6 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.F6.wav";
static std::string A5_6 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.G6.wav";
static std::string A6_6 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.A6.wav";
static std::string A7_6 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.B6.wav";

static std::string A1_7 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.C7.wav";
static std::string A2_7 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.D7.wav";
static std::string A3_7 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.E7.wav";
static std::string A4_7 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.F7.wav";
static std::string A5_7 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.G7.wav";
static std::string A6_7 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.A7.wav";
static std::string A7_7 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.B7.wav";

namespace Rocket {
    void Piano::PreInitialize()
    {
        PushLayer(new PianoLayer());
    }

    void Piano::PostInitialize()
    {
        
    }

    void Piano::PreInitializeModule()
    {
        RK_INFO("Build Type: {0}", BUILD_TYPE);
        RK_INFO("Source Dir: {0}", ProjectSourceDir);

        PushModule(g_ProcessManager);
        PushModule(g_WindowManager);
        PushModule(g_AudioManager);
    }

    void Piano::PostInitializeModule()
    {
        g_AudioManager->LoadAudio(A1_1);
        g_AudioManager->LoadAudio(A2_1);
        g_AudioManager->LoadAudio(A3_1);
        g_AudioManager->LoadAudio(A4_1);
        g_AudioManager->LoadAudio(A5_1);
        g_AudioManager->LoadAudio(A6_1);
        g_AudioManager->LoadAudio(A7_1);

        g_AudioManager->LoadAudio(A1_2);
        g_AudioManager->LoadAudio(A2_2);
        g_AudioManager->LoadAudio(A3_2);
        g_AudioManager->LoadAudio(A4_2);
        g_AudioManager->LoadAudio(A5_2);
        g_AudioManager->LoadAudio(A6_2);
        g_AudioManager->LoadAudio(A7_2);

        g_AudioManager->LoadAudio(A1_3);
        g_AudioManager->LoadAudio(A2_3);
        g_AudioManager->LoadAudio(A3_3);
        g_AudioManager->LoadAudio(A4_3);
        g_AudioManager->LoadAudio(A5_3);
        g_AudioManager->LoadAudio(A6_3);
        g_AudioManager->LoadAudio(A7_3);

        g_AudioManager->LoadAudio(A1_4);
        g_AudioManager->LoadAudio(A2_4);
        g_AudioManager->LoadAudio(A3_4);
        g_AudioManager->LoadAudio(A4_4);
        g_AudioManager->LoadAudio(A5_4);
        g_AudioManager->LoadAudio(A6_4);
        g_AudioManager->LoadAudio(A7_4);

        g_AudioManager->LoadAudio(A1_5);
        g_AudioManager->LoadAudio(A2_5);
        g_AudioManager->LoadAudio(A3_5);
        g_AudioManager->LoadAudio(A4_5);
        g_AudioManager->LoadAudio(A5_5);
        g_AudioManager->LoadAudio(A6_5);
        g_AudioManager->LoadAudio(A7_5);

        g_AudioManager->LoadAudio(A1_6);
        g_AudioManager->LoadAudio(A2_6);
        g_AudioManager->LoadAudio(A3_6);
        g_AudioManager->LoadAudio(A4_6);
        g_AudioManager->LoadAudio(A5_6);
        g_AudioManager->LoadAudio(A6_6);
        g_AudioManager->LoadAudio(A7_6);

        g_AudioManager->LoadAudio(A1_7);
        g_AudioManager->LoadAudio(A2_7);
        g_AudioManager->LoadAudio(A3_7);
        g_AudioManager->LoadAudio(A4_7);
        g_AudioManager->LoadAudio(A5_7);
        g_AudioManager->LoadAudio(A6_7);
        g_AudioManager->LoadAudio(A7_7);
    }

    Application* CreateApplication()
    {
        return static_cast<Application*>(new Piano);
    }
}