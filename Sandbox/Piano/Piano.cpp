#include "Piano.h"
#include "PianoLayer.h"

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
        std::string A0_1 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.C2.wav";
        std::string A1_1 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.D2.wav";
        std::string A2_1 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.E2.wav";
        std::string A3_1 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.F2.wav";
        std::string A4_1 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.G2.wav";
        std::string A5_1 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.A2.wav";
        std::string A6_1 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.B2.wav";
        //std::string A7_1 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.C3.wav";

        std::string A0 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.C3.wav";
        std::string A1 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.D3.wav";
        std::string A2 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.E3.wav";
        std::string A3 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.F3.wav";
        std::string A4 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.G3.wav";
        std::string A5 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.A3.wav";
        std::string A6 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.B3.wav";
        std::string A7 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.C4.wav";

        //std::string A0_2 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.C4.wav";
        std::string A1_2 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.D4.wav";
        std::string A2_2 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.E4.wav";
        std::string A3_2 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.F4.wav";
        std::string A4_2 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.G4.wav";
        std::string A5_2 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.A4.wav";
        std::string A6_2 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.B4.wav";
        std::string A7_2 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.C5.wav";

        std::string A1_3 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.D5.wav";
        std::string A2_3 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.E5.wav";
        std::string A3_3 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.F5.wav";
        std::string A4_3 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.G5.wav";
        std::string A5_3 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.A5.wav";
        std::string A6_3 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.B5.wav";
        std::string A7_3 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.C6.wav";

        g_AudioManager->LoadAudio(A0);
        g_AudioManager->LoadAudio(A1);
        g_AudioManager->LoadAudio(A2);
        g_AudioManager->LoadAudio(A3);
        g_AudioManager->LoadAudio(A4);
        g_AudioManager->LoadAudio(A5);
        g_AudioManager->LoadAudio(A6);
        g_AudioManager->LoadAudio(A7);

        g_AudioManager->LoadAudio(A0_1);
        g_AudioManager->LoadAudio(A1_1);
        g_AudioManager->LoadAudio(A2_1);
        g_AudioManager->LoadAudio(A3_1);
        g_AudioManager->LoadAudio(A4_1);
        g_AudioManager->LoadAudio(A5_1);
        g_AudioManager->LoadAudio(A6_1);
        //g_AudioManager->LoadAudio(A7_1);

        //g_AudioManager->LoadAudio(A0_2);
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
    }

    Application* CreateApplication()
    {
        return static_cast<Application*>(new Piano);
    }
}