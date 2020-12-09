/*
    When you want to create a new application based on RocketGE,
    you should create a new layer with an application.
*/
#include "SandboxApp.h"
#include "ExampleLayer.h"

namespace Rocket
{
    void SimpleSandbox::PreInitialize()
    {
        PushLayer(new ExampleLayer());
    }

    void SimpleSandbox::PreInitializeModule()
    {
        RK_INFO("Build Type: {0}", BUILD_TYPE);
        RK_INFO("Source Dir: {0}", ProjectSourceDir);

        PushModule(Rocket::g_ProcessManager);
        PushModule(Rocket::g_AudioManager);
        PushModule(Rocket::g_WindowManager);
    }

    Application* CreateApplication()
    {
        return static_cast<Application*>(new SimpleSandbox);
    }
}
