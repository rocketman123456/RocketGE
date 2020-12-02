/*
    When you want to create a new application based on RocketGE,
    you should create a new layer with an application.
*/
#include "SandboxApp.h"
#include "ExampleLayer.h"

namespace Rocket
{
    SimpleSandbox::SimpleSandbox()
    {
        RK_INFO("Build Type: {0}", BUILD_TYPE);
        RK_INFO("Source Dir: {0}", ProjectSourceDir);
        PushLayer(new ExampleLayer());
    }

    Application* CreateApplication()
    {
        return static_cast<Application*>(new SimpleSandbox);
    }
}
