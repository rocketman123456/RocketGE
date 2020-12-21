#include "RKEngine.h"
#include "GameLayer.h"

class SimpleGame : public Rocket::Application
{
public:
    virtual void PostInitialize() override
    {
        PushLayer(new GameLayer());
    }

    virtual void PreInitializeModule() override
    {
        RK_INFO("Build Type: {0}", BUILD_TYPE);
        RK_INFO("Source Dir: {0}", ProjectSourceDir);

        PushModule(Rocket::g_ProcessManager);
        PushModule(Rocket::g_AudioManager);
        PushModule(Rocket::g_WindowManager);
    }

    virtual void PostInitializeModule() override
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

        Rocket::g_AudioManager->LoadAudio(A0);
        Rocket::g_AudioManager->LoadAudio(A1);
        Rocket::g_AudioManager->LoadAudio(A2);
        Rocket::g_AudioManager->LoadAudio(A3);
        Rocket::g_AudioManager->LoadAudio(A4);
        Rocket::g_AudioManager->LoadAudio(A5);
        Rocket::g_AudioManager->LoadAudio(A6);
        Rocket::g_AudioManager->LoadAudio(A7);

        Rocket::g_AudioManager->LoadAudio(A0_1);
        Rocket::g_AudioManager->LoadAudio(A1_1);
        Rocket::g_AudioManager->LoadAudio(A2_1);
        Rocket::g_AudioManager->LoadAudio(A3_1);
        Rocket::g_AudioManager->LoadAudio(A4_1);
        Rocket::g_AudioManager->LoadAudio(A5_1);
        Rocket::g_AudioManager->LoadAudio(A6_1);
        //Rocket::g_AudioManager->LoadAudio(A7_1);

        //Rocket::g_AudioManager->LoadAudio(A0_2);
        Rocket::g_AudioManager->LoadAudio(A1_2);
        Rocket::g_AudioManager->LoadAudio(A2_2);
        Rocket::g_AudioManager->LoadAudio(A3_2);
        Rocket::g_AudioManager->LoadAudio(A4_2);
        Rocket::g_AudioManager->LoadAudio(A5_2);
        Rocket::g_AudioManager->LoadAudio(A6_2);
        Rocket::g_AudioManager->LoadAudio(A7_2);
    }

    SimpleGame() : Rocket::Application("SimpleGame") {}
    virtual ~SimpleGame() = default;
};

Rocket::Application *Rocket::CreateApplication()
{
    return new SimpleGame();
}