#include "SandboxApp.h"
#include "GECore/Core.h"

/*
When you want to create a new application based on RocketGE,
you should create a new layer with an application.
*/

namespace Rocket
{
    class SimpleSandbox : implements Application
    {
    public:
        SimpleSandbox()
        {
            RK_INFO("Build Type: {0}", BUILD_TYPE);
            RK_INFO("Source Dir: {0}", ProjectSourceDir);
            PushLayer(new ExampleLayer());
        }
        ~SimpleSandbox()
        {

        }
    };

    Application* CreateApplication()
    {
        return static_cast<Application*>(new SimpleSandbox);
    }
}
