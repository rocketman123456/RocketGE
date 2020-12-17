#include "RKEngine.h"

#include "EditorLayer.h"

class EditorApp : implements Rocket::Application
{
public:
    virtual void PreInitialize() override
    {
        PushLayer(new EditorLayer());
    }

    virtual void PostInitialize() override
    {

    }

    virtual void PreInitializeModule() override
    {
        RK_INFO("Build Type: {0}", BUILD_TYPE);
        RK_INFO("Source Dir: {0}", ProjectSourceDir);

        PushModule(Rocket::g_ProcessManager);
        PushModule(Rocket::g_WindowManager);
        PushModule(Rocket::g_AudioManager);
    }

    virtual void PostInitializeModule() override
    {

    }
};

Rocket::Application* Rocket::CreateApplication()
{
    return static_cast<Rocket::Application*>(new EditorApp);
}
