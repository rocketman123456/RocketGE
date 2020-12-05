#include "Piano.h"
#include "PianoLayer.h"

namespace Rocket {
    void Piano::PreInitialize()
    {
        PushLayer(new PianoLayer(m_AudioManager));
    }

    void Piano::PostInitialize()
    {
        
    }

    void Piano::PreInitializeModule()
    {
        RK_INFO("Build Type: {0}", BUILD_TYPE);
        RK_INFO("Source Dir: {0}", ProjectSourceDir);

        m_AudioManager = new AudioManager();
        PushModule(m_AudioManager);
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

        m_AudioManager->LoadAudio(A0);
        m_AudioManager->LoadAudio(A1);
        m_AudioManager->LoadAudio(A2);
        m_AudioManager->LoadAudio(A3);
        m_AudioManager->LoadAudio(A4);
        m_AudioManager->LoadAudio(A5);
        m_AudioManager->LoadAudio(A6);
        m_AudioManager->LoadAudio(A7);
    }

    Application* CreateApplication()
    {
        return static_cast<Application*>(new Piano);
    }
}