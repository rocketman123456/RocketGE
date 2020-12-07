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

        PushModule(g_AudioManager);
    }

    void Piano::PostInitializeModule()
    {
        std::string A0 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.A0.wav";
        std::string A1 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.A1.wav";
        std::string A2 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.A2.wav";
        std::string A3 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.A3.wav";
        std::string A4 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.A4.wav";
        std::string A5 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.A5.wav";
        std::string A6 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.A6.wav";
        std::string A7 = ProjectSourceDir + "/Assets/sounds/Piano.ff/Piano.ff.A7.wav";

        g_AudioManager->LoadAudio(A0);
        g_AudioManager->LoadAudio(A1);
        g_AudioManager->LoadAudio(A2);
        g_AudioManager->LoadAudio(A3);
        g_AudioManager->LoadAudio(A4);
        g_AudioManager->LoadAudio(A5);
        g_AudioManager->LoadAudio(A6);
        g_AudioManager->LoadAudio(A7);
    }

    Application* CreateApplication()
    {
        return static_cast<Application*>(new Piano);
    }
}